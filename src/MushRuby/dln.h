//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/dln.h (ruby)
 *
 * This file has been taken the ruby distribution and may have been modified.
 * For more information on the original see http://www.ruby-lang.org/.
 *
 * This file may contain original work and modifications by Andy Southgate.
 * In regard to these the author and his employer (Mushware Limited)
 * irrevocably waive all of their copyright rights vested in this particular
 * version of this file to the furthest extent permitted.  The author and
 * Mushware Limited also irrevocably waive any and all of their intellectual
 * property rights arising from said file and its modification and/or additions
 * that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.  This waiver does not
 * affect the rights of the original author or authors.
 *
 * This software carries NO WARRANTY of any kind from Andy Southgate or
 * Mushware Limited.
 *
 ****************************************************************************/
//%Header } qDMnDOsFf3F/Q3dL/SUCGQ
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
