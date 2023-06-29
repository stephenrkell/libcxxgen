# pkg-config doesn't understand PKG_CXXFLAGS, but I'm buggered
# if I'm going to have my Makefiles use _CFLAGS to mean _CXXFLAGS.
# So, if we find we have _CFLAGS set for these, either from pkg.m4
# or because pkg.m4 told the user to set this var, and if we *don't*
# have _CXXFLAGS for these things, propagate. Only one of the USER_*_CFLAGS
# and *_CFLAGS should be non-empty. Note that if we got this far,
# we *must* have a _CFLAGS, even if the user (sanely) didn't call it that,
# because pkg-config will have complained if we didn't fake it up.
if SUPPLIED_LIBCXXFILENO_CFLAGS
LIBCXXFILENO_CXXFLAGS = $(USER_LIBCXXFILENO_CFLAGS)
else
LIBCXXFILENO_CXXFLAGS = $(LIBCXXFILENO_CFLAGS)
endif
if SUPPLIED_LIBDWARFPP_CFLAGS
LIBDWARFPP_CXXFLAGS = $(USER_LIBDWARFPP_CFLAGS)
else
LIBDWARFPP_CXXFLAGS = $(LIBDWARFPP_CFLAGS)
endif
if SUPPLIED_LIBSRK31CXX_CFLAGS
LIBSRK31CXX_CXXFLAGS = $(USER_LIBSRK31CXX_CFLAGS)
else
LIBSRK31CXX_CXXFLAGS = $(LIBSRK31CXX_CFLAGS)
endif

ACLOCAL_AMFLAGS = -I m4
AM_CXXFLAGS = -std=c++11 -g -Wall -Wno-deprecated-declarations -Iinclude -Iinclude/cxxgen $(LIBDWARFPP_CXXFLAGS) $(LIBSRK31CXX_CXXFLAGS) $(LIBCXXFILENO_CXXFLAGS)

cxxgen_includedir = $(includedir)/cxxgen
cxxgen_include_HEADERS = include/cxxgen/cxx_compiler.hpp include/cxxgen/dwarf.hpp include/cxxgen/tokens.hpp

extra_DIST = libcxxgen.pc.in
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libcxxgen.pc

lib_LTLIBRARIES = src/libcxxgen.la
src_libcxxgen_la_SOURCES = src/cxx_compiler.cpp src/cxxgen.cc
src_libcxxgen_la_LIBADD = $(LIBDWARFPP_LIBS)

export LIBCXXFILENO_CXXFLAGS LIBCXXFILENO_LIBS \
LIBSRK31CXX_CXXFLAGS LIBSRK31CXX_LIBS \
LIBDWARFPP_CXXFLAGS LIBDWARFPP_LIBS

lib/libcxxgen.so: $(lib_LTLIBRARIES)
	mkdir -p lib && cd lib && ln -sf ../src/.libs/libcxxgen.so .

lib/libcxxgen.so.0: $(lib_LTLIBRARIES)
	mkdir -p lib && cd lib && ln -sf ../src/.libs/libcxxgen.so.0 .

all: lib/libcxxgen.so lib/libcxxgen.so.0
