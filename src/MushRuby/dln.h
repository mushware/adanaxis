//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/dln.h (ruby)
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
//%Header } pkLilztY0pUXWim+Xg/uNw
/**********************************************************************

  dln.h -

 
  $Date: 2006/04/11 23:30:09 $
  created at: Wed Jan 19 16:53:09 JST 1994

  Copyright (C) 1993-2003 Yukihiro Matsumoto

**********************************************************************/

#ifndef DLN_H
#define DLN_H

#ifdef __cplusplus
# ifndef  HAVE_PROTOTYPES
#  define HAVE_PROTOTYPES 1
# endif
# ifndef  HAVE_STDARG_PROTOTYPES
#  define HAVE_STDARG_PROTOTYPES 1
# endif
#endif

#undef _
#ifdef HAVE_PROTOTYPES
# define _(args) args
#else
# define _(args) ()
#endif

char *dln_find_exe _((const char*,const char*));
char *dln_find_file _((const char*,const char*));

#ifdef USE_DLN_A_OUT
extern char *dln_argv0;
#endif

void *dln_load _((const char*));
#endif
