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

CPPFLAGS=$OLD_CPPFLAGS

# If the user (sanely) supplied _CXXFLAGS, and not _CFLAGS, 
# duplicate the latter to the former.  See rant about pkg-config in Makefile.am.
# We save the old _CFLAGS.
USER_LIBCXXFILENO_CFLAGS="$LIBCXXFILENO_CFLAGS"
LIBCXXFILENO_CFLAGS="$LIBCXXFILENO_CXXFLAGS"
USER_LIBDWARFPP_CFLAGS="$LIBDWARFPP_CFLAGS"
LIBDWARFPP_CFLAGS="$LIBDWARFPP_CXXFLAGS"
USER_LIBSRK31CXX_CFLAGS="$LIBSRK31CXX_CFLAGS"
LIBSRK31CXX_CFLAGS="$LIBSRK31CXX_CXXFLAGS"

# Now, all the information from pkg-config or from user _CXXFLAGS) is in _CFLAGS.
# We might also have USER_ _CFLAGS, if the user did what pkg.m4 stupidly told them.
# We use this information (i.e. propagate to _CXXFLAGS) only if the user *didn't* give us
# _CXXFLAGS.
AM_CONDITIONAL(SUPPLIED_LIBCXXFILENO_CFLAGS, [test x"$USER_LIBCXXFILENO_CFLAGS" != x && test x"$LIBCXXFILENO_CXXFLAGS" = x])
AM_CONDITIONAL(SUPPLIED_LIBDWARFPP_CFLAGS, [test x"$USER_LIBDWARFPP_CFLAGS" != x && test x"$LIBDWARFPP_CXXFLAGS" = x])
AM_CONDITIONAL(SUPPLIED_LIBSRK31CXX_CFLAGS, [test x"$USER_LIBSRK31CXX_CFLAGS" != x && test x"$LIBSRK31CXX_CXXFLAGS" = x])

PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([LIBDWARFPP], [libdwarfpp])

AC_OUTPUT([Makefile libcxxgen.pc])
