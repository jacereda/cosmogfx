#include <dlfcn.h>

int
main(int argc, char *argv[])
{
	static void *funcs[] = { dlopen, dlsym, dlclose, dlerror };
	int (*p)(void **, int, char **) = (int (*)())argv[argc];
	return p(funcs, argc, argv);
}
