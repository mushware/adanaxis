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
 * In regard to these Andy Southgate irrevocably waives all copyright
 * rights vested in said original work and modifications.
 *
 * This software carries NO WARRANTY of any kind from Andy Southgate.
 *
 ****************************************************************************/
//%Header } h4LK83ZDQi2h8BnTD1hdAg
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
