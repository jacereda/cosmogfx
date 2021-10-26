
#include "dtrampoline.h"

asm("template:\n\t"
    "push %rbp \n\t"
    "mov %rsp,%rbp \n\t"
    "mov $__sysv2nt,%rax \n\t"
    "push %rax \n\t"
    "movabs $0xdeadbeeffeedc0de,%rax\n\t"
    "ret");

static uint8_t *mem;

void
dtrampoline_init()
{
	mem = VirtualAlloc(0, 0x10000, 0x3000, 0x40);
}

void *
dtrampoline(void *f, unsigned arity)
{
	if (!f)
		return 0;
	void *template();
	uint8_t *  r = mem;
	uintptr_t *p = (uintptr_t *)(r + 14);
	uint32_t * a = (uint32_t *)(r + 7);
	memcpy(r, template, 32);
	*p = (uintptr_t)f;
	void *(__sysv2nt)();
	void *(__sysv2nt6)();
	void *(__sysv2nt8)();
	void *(__sysv2nt10)();
	void *(__sysv2nt12)();
	void *(__sysv2nt14)();
	arity = 14; // XXX
	switch (arity) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		*a = (uint32_t)(uintptr_t)__sysv2nt;
		break;
	case 5:
	case 6:
		*a = (uint32_t)(uintptr_t)__sysv2nt6;
		break;
	case 7:
	case 8:
		*a = (uint32_t)(uintptr_t)__sysv2nt8;
		break;
	case 9:
	case 10:
		*a = (uint32_t)(uintptr_t)__sysv2nt10;
		break;
	case 11:
	case 12:
		*a = (uint32_t)(uintptr_t)__sysv2nt12;
		break;
	case 13:
	case 14:
		*a = (uint32_t)(uintptr_t)__sysv2nt14;
		break;
	}
	mem += 32;
	return r;
}
