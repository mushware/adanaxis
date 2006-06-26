//%includeGuardStart {
#ifndef FILE_H
#define FILE_H
//%includeGuardStart } TdftLyEPwhwF9HRbyOXwhA
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/missing/file.h (ruby)
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
//%Header } jfLjwXkfNgwTqSP9RHg85Q
/* This is file FILE.H */

#ifndef _FILE_H_
#define _FILE_H_

#include <fcntl.h>

#ifndef L_SET
# define L_SET  0       /* seek from beginning.  */
# define L_CURR	1       /* seek from current position.  */
# define L_INCR	1       /* ditto.  */
# define L_XTND 2       /* seek from end.  */
#endif

#ifndef R_OK
# define R_OK  4        /* test whether readable.  */
# define W_OK  2        /* test whether writable.  */
# define X_OK  1        /* test whether execubale. */
# define F_OK  0        /* test whether exist.  */
#endif

#endif
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
