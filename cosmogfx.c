#include "cosmogfx.h"
#include "foreign-dlopen/src/elf_loader.h"
#include "foreign-dlopen/src/foreign_dlopen.h"

void *(*z_dlopen)(const char *filename, int flags);
void *(*z_dlsym)(void *handle, const char *symbol);
int (*z_dlclose)(void *handle);
char *(*z_dlerror)(void);

#include "glcv/src/cv.c"

intptr_t   osEvent_xlib(ev *e);
intptr_t   osEvent_win(ev *e);
extern int cvrun_xlib(int, char **);
extern int cvrun_win(int, char **);

#define cvrun cvrun_xlib
#define osEvent osEvent_xlib
#include "glcv/src/xlib.c"
#undef osEvent
#undef cvrun

#include "../cosmopolitan/libc/isystem/windows.h"
#undef cvrun
#define cvrun cvrun_win
#define osEvent osEvent_win
#include "glcv/src/win.c"
#undef osEvent
#undef cvrun

intptr_t
osEvent(ev *e)
{
	if (IsWindows())
		return osEvent_win(e);
	else
		return osEvent_xlib(e);
}

static int
cont(void **p, int argc, char **argv)
{
	z_dlopen = p[0];
	z_dlsym = p[1];
	z_dlclose = p[2];
	z_dlerror = p[3];

	cvrun_xlib(argc, argv);
}

static const char *
guess_interp(char *buf, size_t sz)
{
	FILE *f = popen("readelf -Wp.interp /usr/bin/env", "r");
	assert(f);
	size_t n = fread(buf, 1, sz, f);
	assert(n);
	pclose(f);
	const char *r = strchr(buf, '/');
	assert(r);
	*strchr(r, '\n') = 0;
	return r;
}

int
cosmogfx_init(int argc, char **argv)
{
	dtrampoline_init();
	if (IsWindows())
		cvrun_win(argc, argv);
	else {
		init_exec_elf(argv);
		argv[argc] = (char *)cont;
		char	    buf[256];
		const char *interp = guess_interp(buf, sizeof(buf));
		exec_elf("/zip/b/helper", interp, argc, argv);
	}
}

STATIC_YOINK("zip_uri_support");
