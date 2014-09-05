AC_INIT([SmartHistos], [1.0], [jp.araque@cern.ch])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
#AM_SILENT_RULES([yes])
AM_PROG_AR
AC_PROG_CXX
#AX_CXX_COMPILE_STDCXX_11
AC_PROG_CXX
AC_CONFIG_MACRO_DIR([m4])
AC_PREFIX_DEFAULT(`pwd`/..)
AC_CONFIG_HEADERS([Config.h])
AC_LANG_PUSH([C++])
LT_INIT

# Check for tr1 or not
AC_CHECK_HEADER(tr1/unordered_map,[AC_DEFINE([HAVE_TR1],[],["Have tr1"])],[])
AC_CHECK_HEADER(unordered_map,[AC_DEFINE([HAVE_CXX0X],[],["Have C++0x"])],[])

#Cofigure files
AC_CONFIG_FILES([
                 Makefile
                 src/Makefile
                 example/Makefile])
AC_OUTPUT

