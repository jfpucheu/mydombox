#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(mydombox, 0.5.2, jfpucheu@gmail.com)
AC_CANONICAL_HOST
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE

AC_PREFIX_DEFAULT(/usr/local)

## first initialises parameters to the standard Sympa filesystem organization
# $prefix variable initialisation seems to be tricky
if test "$prefix" = "NONE"; then
   prefix=$ac_default_prefix
fi

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET
AM_PROG_CC_C_O

# MYSQL
AC_PATH_PROGS(MYSQL_CONFIG, mysql_config)
if ! test -x "$MYSQL_CONFIG"; then
AC_MSG_ERROR([mysql configuration script was not found])
fi
MYSQL_CFLAGS=`$MYSQL_CONFIG --cflags`
MYSQL_LDFLAGS=`$MYSQL_CONFIG --libs`
AC_SUBST(MYSQL_CONFIG)
AC_SUBST(MYSQL_CFLAGS)
AC_SUBST(MYSQL_LDFLAGS)

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
