AC_INIT(Colorasion, 0.0.1)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR(src/colorasion_main.hxx)
AM_INIT_AUTOMAKE(dist-bzip2)

AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

dnl AC_DISABLE_SHARED
dnl AC_PROG_LIBTOOL

AC_PROG_RANLIB

AC_LANG(C++)

dnl Checking for libraries

dnl -------------------------
dnl Check for Maintainer Mode
dnl -------------------------
AC_MSG_CHECKING(for maintainer mode)
AC_ARG_ENABLE(maintainer-mode, AC_HELP_STRING([--enable-maintainer-mode], [Enable maintainer mode]),, enable_maintainer_mode="no")

if test "$enable_maintainer_mode" != "no"; then
    CXXFLAGS="$CXXFLAGS -g -O0 -Wall -Werror"
    AC_MSG_RESULT([enabled])
else
    AC_MSG_RESULT([disabled])
fi

dnl Checking for libraries
AC_CHECK_LIB(qthreads, main)
AC_CHECK_LIB(guile, scm_boot_guile)
AC_CHECK_HEADER(guile/gh.h)

dnl FIXME: this is a hack for my local machine...
dnl LIBS="$LIBS -L/usr/X11R6/lib/ -lXxf86vm"

REQUIRED_CLANLIB_VERSION="0.7.4"

PKG_CHECK_MODULES(FEUERKRAFT_DEPS,
 [
  clanCore-0.7    >= $REQUIRED_CLANLIB_VERSION
  clanApp-0.7     >= $REQUIRED_CLANLIB_VERSION
  clanDisplay-0.7 >= $REQUIRED_CLANLIB_VERSION
  clanGL-0.7      >= $REQUIRED_CLANLIB_VERSION
  clanSound-0.7   >= $REQUIRED_CLANLIB_VERSION
  ],
 [CXXFLAGS="$CXXFLAGS $FEUERKRAFT_DEPS_CFLAGS"
  LIBS="$LIBS $FEUERKRAFT_DEPS_LIBS"])

AC_OUTPUT( Makefile
           data/Makefile 
           src/Makefile 
           src/input/Makefile 
)

dnl Local Variables:
dnl compile-command: "./autogen.sh && ./configure"
dnl End:

dnl EOF
