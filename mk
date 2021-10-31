#!/usr/bin/env bash
set -e
install -d b
gcc -s -ffunction-sections -fdata-sections -Wl,-gc-sections -fomit-frame-pointer -Os -pie helper.c -o b/helper.linux -ldl
../cosmopolitan/build/bootstrap/zipobj.com  -b0x400000 -o b/helper.linux.zip.o b/helper.linux
# ../cosmopolitan/build/bootstrap/zipobj.com  -b0x400000 -o b/helper.obsd.zip.o b/helper.obsd
# ../cosmopolitan/build/bootstrap/zipobj.com  -b0x400000 -o b/helper.fbsd.zip.o b/helper.fbsd
# ../cosmopolitan/build/bootstrap/zipobj.com  -b0x400000 -o b/helper.nbsd.zip.o b/helper.nbsd
gcc -c foreign-dlopen/src/amd64/z_trampo.S -o b/z_trampo.o
cosmoc -DDLOPEN=z_dlopen -DDLSYM=z_dlsym \
       -DZ_SMALL -DSTDLIB=1 -DELFCLASS=ELFCLASS64 \
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
       b/helper.linux.zip.o \
       -o b/demo.com.dbg
objcopy --strip-all -Obinary b/demo.com.dbg b/demo.com
# scp b/demo.com curro:
# scp -P2222 b/demo.com  localhost:/tmp
# ssh -p2222 localhost /tmp/demo.com
