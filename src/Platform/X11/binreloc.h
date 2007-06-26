//%includeGuardStart {
#ifndef BINRELOC_H
#define BINRELOC_H
//%includeGuardStart } ukjQBryvOHbQowNp1xHitg
//%Header {
/*****************************************************************************
 *
 * File: src/Platform/X11/binreloc.h (ruby)
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
//%Header } FuFFDJgvK7vwtiW6eognUw
/*
 * BinReloc - a library for creating relocatable executables
 * Written by: Hongli Lai <h.lai@chello.nl>
 * http://autopackage.org/
 *
 * This source code is public domain. You can relicense this code
 * under whatever license you want.
 *
 * See http://autopackage.org/docs/binreloc/ for
 * more information and how to use this.
 */

#ifndef __BINRELOC_H__
#define __BINRELOC_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/** These error codes can be returned by br_init(), br_init_lib(), gbr_init() or gbr_init_lib(). */
typedef enum {
	/** Cannot allocate memory. */
	BR_INIT_ERROR_NOMEM,
	/** Unable to open /proc/self/maps; see errno for details. */
	BR_INIT_ERROR_OPEN_MAPS,
	/** Unable to read from /proc/self/maps; see errno for details. */
	BR_INIT_ERROR_READ_MAPS,
	/** The file format of /proc/self/maps is invalid; kernel bug? */
	BR_INIT_ERROR_INVALID_MAPS,
	/** BinReloc is disabled (the ENABLE_BINRELOC macro is not defined). */
	BR_INIT_ERROR_DISABLED
} BrInitError;


#ifndef BINRELOC_RUNNING_DOXYGEN
/* Mangle symbol names to avoid symbol collisions with other ELF objects. */
	#define br_init             xRMS95840226266325_br_init
	#define br_init_lib         xRMS95840226266325_br_init_lib
	#define br_find_exe         xRMS95840226266325_br_find_exe
	#define br_find_exe_dir     xRMS95840226266325_br_find_exe_dir
	#define br_find_prefix      xRMS95840226266325_br_find_prefix
	#define br_find_bin_dir     xRMS95840226266325_br_find_bin_dir
	#define br_find_sbin_dir    xRMS95840226266325_br_find_sbin_dir
	#define br_find_data_dir    xRMS95840226266325_br_find_data_dir
	#define br_find_locale_dir  xRMS95840226266325_br_find_locale_dir
	#define br_find_lib_dir     xRMS95840226266325_br_find_lib_dir
	#define br_find_libexec_dir xRMS95840226266325_br_find_libexec_dir
	#define br_find_etc_dir     xRMS95840226266325_br_find_etc_dir
	#define br_strcat           xRMS95840226266325_br_strcat
	#define br_build_path       xRMS95840226266325_br_build_path
	#define br_dirname          xRMS95840226266325_br_dirname


#endif
int   br_init             (BrInitError *error);
int   br_init_lib         (BrInitError *error);

char *br_find_exe         (const char *default_exe);
char *br_find_exe_dir     (const char *default_dir);
char *br_find_prefix      (const char *default_prefix);
char *br_find_bin_dir     (const char *default_bin_dir);
char *br_find_sbin_dir    (const char *default_sbin_dir);
char *br_find_data_dir    (const char *default_data_dir);
char *br_find_locale_dir  (const char *default_locale_dir);
char *br_find_lib_dir     (const char *default_lib_dir);
char *br_find_libexec_dir (const char *default_libexec_dir);
char *br_find_etc_dir     (const char *default_etc_dir);

/* Utility functions */
char *br_strcat  (const char *str1, const char *str2);
char *br_build_path (const char *dir, const char *file);
char *br_dirname (const char *path);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BINRELOC_H__ */
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
