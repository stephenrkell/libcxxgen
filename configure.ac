AC_CONFIG_MACRO_DIR([m4])
AC_PREREQ([2.69])
AC_INIT([libcxxgen], [0.1], [srk31@cl.cam.ac.uk])
AC_CONFIG_SRCDIR([include/cxxgen/dwarf.hpp])
CFLAGS="-I$prefix/include $CFLAGS"
CXXFLAGS="-I$prefix/include $CXXFLAGS"
LDFLAGS="-L$prefix/lib $LDFLAGS"
PKG_CONFIG_PATH="$prefix/lib/pkgconfig:$PKG_CONFIG_PATH"
export CFLAGS CXXFLAGS LDFLAGS PKG_CONFIG_PATH
LT_INIT
AC_LANG([C++])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wno-portability])
AM_MAINTAINER_MODE
AC_PROG_CXX

AX_CXX_COMPILE_STDCXX_11
CPPFLAGS="-std=c++11 $CPPFLAGS"
export CPPFLAGS

AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])
AC_PROG_LN_S
AC_PROG_INSTALL

AC_CHECK_HEADERS([cstdlib cstring fstream map memory sstream string], [], [AC_MSG_FAILURE([required standard headers: cstdlib cstring fstream map memory sstream string])])

PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([LIBDWARFPP], [libdwarfpp])

AC_OUTPUT([Makefile libcxxgen.pc])
