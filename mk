#!/usr/bin/env bash
set -e
install -d b
gcc -s -ffunction-sections -fdata-sections -Wl,-gc-sections -fomit-frame-pointer -Os -pie -fPIC helper.c -o helper/linux -ldl
zipobj.com  -b0x400000 -o b/helper.linux.zip.o helper/linux
zipobj.com  -b0x400000 -o b/helper.obsd.zip.o helper/obsd
zipobj.com  -b0x400000 -o b/helper.fbsd.zip.o helper/fbsd
zipobj.com  -b0x400000 -o b/helper.nbsd.zip.o helper/nbsd
cosmoc -DDLOPEN=z_dlopen \
       -DDLSYM=z_dlsym \
       -DZ_SMALL \
       -DSTDLIB=1 \
       -DELFCLASS=ELFCLASS64 \
       -DCV_NO_MAIN \
       -DCV_DYN \
       -include cosmopolitan.h \
       -I. \
       -Imicroui/demo \
       -Imicroui/src \
       -Ifake \
       -Iglcv/src \
       -fno-stack-protector \
       -ffunction-sections \
       -fdata-sections \
       -Wl,-gc-sections \
       cosmogfx.c \
       dtrampoline.c \
       gl.c \
       demo.c \
       microui/src/microui.c \
       renderer.c \
       elf_loader.c \
       b/helper.linux.zip.o \
       b/helper.obsd.zip.o \
       b/helper.fbsd.zip.o \
       b/helper.nbsd.zip.o \
       -o b/demo.com.dbg
objcopy --strip-all -Obinary b/demo.com.dbg b/demo.com
# scp b/demo.com curro:
scp -P2222 b/demo.com  localhost:
ssh -XY -p2222 localhost ./demo.com
