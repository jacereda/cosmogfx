void elf_exec(
    const char *file, const char *interp, int argc, char **argv, char **envp);
void elf_interp(char *buf, size_t sz, const char *file);
