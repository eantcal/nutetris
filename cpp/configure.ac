#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([nutetris], [1.23], [acaldmail@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([tetris_piece_T.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdlib.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([select])

# Checks for libraries.
AC_PATH_X
AC_CHECK_LIB([X11], [XDrawLine])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
