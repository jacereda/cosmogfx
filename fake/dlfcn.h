void *(*z_dlopen)(const char *filename, int flags);
void *(*z_dlsym)(void *handle, const char *symbol);
int (*z_dlclose)(void *handle);
char *(*z_dlerror)(void);

#define dlopen z_dlopen
#define dlsym z_dlsym
#define dlclose z_dlclose
#define dlerror z_dlerror
