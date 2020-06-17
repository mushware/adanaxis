//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/util.h (ruby)
 *
 * This file has been taken the ruby distribution and may have been modified.
 * For more information on the original see http://www.ruby-lang.org/.
 *
 * This file may contain original work and modifications by Andy Southgate.
 * In regard to these Andy Southgate irrevocably waives all copyright
 * rights vested in said original work and modifications.
 *
 * This software carries NO WARRANTY of any kind from Andy Southgate.
 *
 ****************************************************************************/
//%Header } sm9ivAtTyXeJbgmJVDhtqw
/**********************************************************************

  util.h -

 
  $Date: 2006/04/11 23:30:11 $
  created at: Thu Mar  9 11:55:53 JST 1995

  Copyright (C) 1993-2003 Yukihiro Matsumoto

**********************************************************************/

#ifndef UTIL_H
#define UTIL_H

#ifndef _
#ifdef __cplusplus
# ifndef  HAVE_PROTOTYPES
#  define HAVE_PROTOTYPES 1
# endif
# ifndef  HAVE_STDARG_PROTOTYPES
#  define HAVE_STDARG_PROTOTYPES 1
# endif
#endif
#ifdef HAVE_PROTOTYPES
# define _(args) args
#else
# define _(args) ()
#endif
#ifdef HAVE_STDARG_PROTOTYPES
# define __(args) args
#else
# define __(args) ()
#endif
#endif

#define scan_oct ruby_scan_oct
unsigned long scan_oct _((const char*, int, int*));
#define scan_hex ruby_scan_hex
unsigned long scan_hex _((const char*, int, int*));

#if defined(MSDOS) || defined(__CYGWIN32__) || defined(_WIN32)
void ruby_add_suffix();
#endif

void ruby_qsort _((void*, const int, const int, int (*)(), void*));
#define qsort(b,n,s,c,d) ruby_qsort(b,n,s,c,d)

void ruby_setenv _((const char*, const char*));
void ruby_unsetenv _((const char*));
#undef setenv
#undef unsetenv
#define setenv(name,val) ruby_setenv(name,val)
#define unsetenv(name,val) ruby_unsetenv(name);

char *ruby_strdup _((const char*));
#undef strdup
#define strdup(s) ruby_strdup(s)

char *ruby_getcwd _((void));
#define my_getcwd() ruby_getcwd()

double ruby_strtod _((const char*, char **));
#undef strtod
#define strtod(s,e) ruby_strtod(s,e)

#endif /* UTIL_H */
