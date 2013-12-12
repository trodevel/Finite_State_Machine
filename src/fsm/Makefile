# Makefile for libfsm
# Copyright (C) 2013 Sergey Kolevatov

LIBNAME=libfsm

CC=gcc

CFLAGS=-O3 -Wall -D_LARGEFILE64_SOURCE=1
#CFLAGS=-O -DMAX_WBITS=14 -DMAX_MEM_LEVEL=7
#CFLAGS=-g -DDEBUG
#CFLAGS=-O3 -Wall -Wwrite-strings -Wpointer-arith -Wconversion \
#           -Wstrict-prototypes -Wmissing-prototypes

SFLAGS=-O3 -fPIC -D_LARGEFILE64_SOURCE=1
LDFLAGS= -L. libfsm.a
TEST_LDFLAGS=-L. libfsm.a
LDSHARED=gcc
CPP=gcc -E

STATICLIB=libfsm.a
SHAREDLIB=
SHAREDLIBV=
SHAREDLIBM=
LIBS=$(STATICLIB) $(SHAREDLIBV)

AR=ar rc
RANLIB=ranlib
LDCONFIG=ldconfig
LDSHAREDLIBC=-lc
TAR=tar
SHELL=/bin/sh
EXE=

prefix =/usr/local
exec_prefix =${prefix}
libdir =${exec_prefix}/lib
sharedlibdir =${libdir}
includedir =${prefix}/include
mandir =${prefix}/share/man
man3dir = ${mandir}/man3
pkgconfigdir = ${libdir}/pkgconfig

OBJC = parameter.o

PIC_OBJC = parameter.lo

# to use the asm code: make OBJA=match.o, PIC_OBJA=match.lo
OBJA =
PIC_OBJA =

OBJS = $(OBJC) $(OBJA)

PIC_OBJS = $(PIC_OBJC) $(PIC_OBJA)

all: static

static: example$(EXE)

shared: example_sh$(EXE)

check: test

test: all teststatic

teststatic: static
	@echo static test is not ready yet, dc10
 
testshared: shared
	@LD_LIBRARY_PATH=`pwd`:$(LD_LIBRARY_PATH) ; export LD_LIBRARY_PATH; \
	LD_LIBRARYN32_PATH=`pwd`:$(LD_LIBRARYN32_PATH) ; export LD_LIBRARYN32_PATH; \
	DYLD_LIBRARY_PATH=`pwd`:$(DYLD_LIBRARY_PATH) ; export DYLD_LIBRARY_PATH; \
	SHLIB_PATH=`pwd`:$(SHLIB_PATH) ; export SHLIB_PATH; \
	echo shared library test is not ready yet, dc10

libfsm.a: $(OBJS)
	$(AR) $@ $(OBJS)
	-@ ($(RANLIB) $@ || true) >/dev/null 2>&1

%o.: %.cpp
	-@mkdir objs 2>/dev/null || test -d objs
	$(CC) $(SFLAGS) -DPIC -c -o objs/$*.o $<
	-@mv objs/$*.o $@

$(SHAREDLIBV): $(PIC_OBJS)
	$(LDSHARED) $(SFLAGS) -o $@ $(PIC_OBJS) $(LDSHAREDLIBC) $(LDFLAGS)
	rm -f $(SHAREDLIB) $(SHAREDLIBM)
	ln -s $@ $(SHAREDLIB)
	ln -s $@ $(SHAREDLIBM)
	-@rmdir objs

example$(EXE): example.o $(STATICLIB)
	$(CC) $(CFLAGS) -o $@ example.o $(TEST_LDFLAGS)

example_sh$(EXE): example.o $(SHAREDLIBV)
	$(CC) $(CFLAGS) -o $@ example.o -L. $(SHAREDLIBV)

# The ranlib in install is needed on NeXTSTEP which checks file times
# ldconfig is for Linux

mostlyclean: clean
clean:
	rm -f *.o *.lo *~ \
	   example$(EXE) example_sh$(EXE) \
	   libfsm.* so_locations \
	rm -rf objs
