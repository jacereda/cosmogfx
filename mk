#!/usr/bin/env bash
set -e
install -d b
gcc -c foreign-dlopen/src/amd64/z_trampo.S -o b/z_trampo.o
gcc helper.c -Wl,-Ttext-segment,0x40000000 -o b/helper -ldl
../cosmopolitan/build/bootstrap/zipobj.com  -b0x400000 -o b/helper.zip.o b/helper
cosmoc -DDLOPEN=z_dlopen -DDLSYM=z_dlsym -Dmmap=__sys_mmap -Dmprotect=sys_mprotect -Dmunmap=sys_munmap \
       -DZ_SMALL -DSTDLIB=1 -DAT_NULL=0 -DELFCLASS=ELFCLASS64 \
       -DCV_NO_MAIN -DCV_DYN \
       -I../cosmopolitan -I. -Imicroui/demo -Imicroui/src -Ifake -Iglcv/src \
       -ffunction-sections -fdata-sections -Wl,-gc-sections \
       -Os \
       cosmogfx.c \
       dtrampoline.c \
       gl.c \
       demo.c \
       microui/src/microui.c \
       renderer.c \
       foreign-dlopen/src/loader.c \
       b/z_trampo.o \
       b/helper.zip.o \
       -o b/demo.com.dbg
objcopy --strip-all -Obinary b/demo.com.dbg b/demo.com
# scp b/demo.com curro:
