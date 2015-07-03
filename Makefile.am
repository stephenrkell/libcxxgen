ACLOCAL_AMFLAGS = -I m4
AM_CXXFLAGS = -std=c++11 -Wall -Wno-deprecated-declarations -Iinclude -Iinclude/cxxgen $(LIBDWARFPP_CFLAGS)

cxxgen_includedir = $(includedir)/cxxgen
cxxgen_include_HEADERS = include/cxxgen/cxx_compiler.hpp include/cxxgen/dwarf.hpp include/cxxgen/tokens.hpp

extra_DIST = libcxxgen.pc.in
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libcxxgen.pc

lib_LTLIBRARIES = src/libcxxgen.la
src_libcxxgen_la_SOURCES = src/cxx_compiler.cpp src/cxxgen.cc
src_libcxxgen_la_LIBADD = $(LIBDWARFPP_LIBS)

