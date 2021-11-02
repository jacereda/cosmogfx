#include "elf_loader.h"
#include "libc/calls/internal.h"

static const unsigned align_mask = 4095;

static uintptr_t
pgtrunc(uintptr_t x)
{
	return x & ~align_mask;
}

static uintptr_t
pground(uintptr_t x)
{
	return pgtrunc(x + align_mask);
}

static unsigned
pflags(unsigned x)
{
	unsigned r = 0;
	if (x & PF_R)
		r += PROT_READ;
	if (x & PF_W)
		r += PROT_WRITE;
	if (x & PF_X)
		r += PROT_EXEC;
	return r;
}

static void
z_fini(void)
{
}

static char *
loadelf_anon(int fd, Elf64_Ehdr *ehdr, Elf64_Phdr *phdr)
{
	bool	  dyn = ehdr->e_type == ET_DYN;
	uintptr_t minva = -1;
	uintptr_t maxva = 0;
	for (Elf64_Phdr *p = phdr; p < &phdr[ehdr->e_phnum]; p++) {
		if (p->p_type != PT_LOAD)
			continue;
		if (p->p_vaddr < minva)
			minva = p->p_vaddr;
		if (p->p_vaddr + p->p_memsz > maxva)
			maxva = p->p_vaddr + p->p_memsz;
	}

	minva = pgtrunc(minva);
	maxva = pground(maxva);

	uint8_t *base = __sys_mmap(
	    0, maxva - minva, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0, 0);
	assert(base != (void *)-1);
	__sys_munmap(base, maxva - minva);
	for (Elf64_Phdr *p = phdr; p < &phdr[ehdr->e_phnum]; p++) {
		if (p->p_type != PT_LOAD)
			continue;
		uintptr_t off = p->p_vaddr & align_mask;
		uint8_t * start = dyn ? base : 0;
		start += pgtrunc(p->p_vaddr);
		size_t	 sz = pground(p->p_memsz + off);
		uint8_t *m = __sys_mmap(start, sz, PROT_WRITE,
		    MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS, -1, 0, 0);
		assert(m != (void *)-1);
		ssize_t sr = lseek(fd, p->p_offset, SEEK_SET);
		assert(sr >= 0);
		ssize_t rr = read(fd, m + off, p->p_filesz);
		assert(rr == (ssize_t)p->p_filesz);
		sys_mprotect(m, sz, pflags(p->p_flags));
	}
	return base;
}

struct loaded {
	char *	   base;
	char *	   entry;
	Elf64_Ehdr eh;
	Elf64_Phdr ph[32];
};

static void
loadfd(struct loaded *l, int fd)
{
	assert(fd >= 0);
	size_t hsz = read(fd, &l->eh, sizeof(l->eh));
	assert(hsz == sizeof(l->eh));
	assert(l->eh.e_phnum < sizeof(l->ph) / sizeof(l->ph[0]));
	int rs = lseek(fd, l->eh.e_phoff, SEEK_SET);
	assert(rs >= 0);
	int rsz = read(fd, l->ph, l->eh.e_phnum * sizeof(l->ph[0]));
	assert(rsz == l->eh.e_phnum * sizeof(l->ph[0]));
	l->entry = (uint8_t *)l->eh.e_entry;
}

static void
load(struct loaded *l, const char *file)
{
	int fd = open(file, O_RDONLY);
	loadfd(l, fd);
	l->base = loadelf_anon(fd, &l->eh, l->ph);
	l->entry += l->eh.e_type == ET_DYN ? (uintptr_t)l->base : 0;
	close(fd);
}

void
elf_interp(char *buf, size_t bsz, const char *file)
{
	int	      fd = open(file, O_RDONLY);
	struct loaded l;
	size_t	      sz;
	loadfd(&l, fd);
	for (unsigned i = 0; i < l.eh.e_phnum; i++)
		switch (l.ph[i].p_type) {
		case PT_INTERP:
			assert(l.ph[i].p_filesz < bsz);
			sz = read(fd, buf, l.ph[i].p_filesz);
			assert(sz == l.ph[i].p_filesz);
			break;
		}
	close(fd);
}

void
elf_exec(
    const char *file, const char *iinterp, int argc, char *argv[], char **envp)
{
	struct loaded prog;
	load(&prog, file);
	struct loaded interp;
	load(&interp, iinterp);

	while (*envp++)
		;
	Elf64_auxv_t *av = (Elf64_auxv_t *)envp;
#define AVSET(t, expr)                                      \
	do {                                                \
		if (av->a_type == (t))                      \
			av->a_un.a_val = (uintptr_t)(expr); \
	} while (0)

	while (av->a_type) {
		AVSET(AT_PHDR, prog.base + prog.eh.e_phoff);
		AVSET(AT_PHENT, prog.eh.e_phentsize);
		AVSET(AT_PHNUM, prog.eh.e_phnum);
		AVSET(AT_PAGESZ, 0x1000);
		AVSET(AT_BASE, interp.base);
		AVSET(AT_FLAGS, 0);
		AVSET(AT_ENTRY, prog.entry);
		AVSET(AT_EXECFN, argv[0]);
		++av;
	}
#undef AVSET
	char **sp = argv - 1;
	asm volatile("mov\t%2,%%rsp\n\t"
		     "jmpq\t*%1"
		     : /* no outputs */
		     : "D"(IsFreebsd() ? sp : 0), "S"(interp.entry), "d"(sp)
		     : "memory");
	unreachable;
}
