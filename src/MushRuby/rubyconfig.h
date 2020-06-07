//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/rubyconfig.h (ruby)
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
//%Header } ADAHCOjv2Yeq+Q/gzosTBw

#ifdef WIN32
/* Win32 version */
#define STDC_HEADERS 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_MEMORY_H 1
#define HAVE_OFF_T 1
#define SIZEOF_INT 4
#define SIZEOF_SHORT 2
#define SIZEOF_LONG 4
#define SIZEOF_LONG_LONG 0
#define SIZEOF___INT64 8
#define SIZEOF_OFF_T 4
#define SIZEOF_VOIDP 4
#define SIZEOF_FLOAT 4
#define SIZEOF_DOUBLE 8
#define SIZEOF_TIME_T 4
#define HAVE_PROTOTYPES 1
#define TOKEN_PASTE(x,y) x##y
#define HAVE_STDARG_PROTOTYPES 1
#define NORETURN(x) __declspec(noreturn) x
#define RUBY_EXTERN extern __declspec(dllimport)
#define HAVE_DECL_SYS_NERR 1
#define HAVE_LIMITS_H 1
#define HAVE_FCNTL_H 1
#define HAVE_SYS_UTIME_H 1
#define HAVE_FLOAT_H 1
#define rb_pid_t int
#define rb_gid_t int
#define rb_uid_t int
#define HAVE_STRUCT_STAT_ST_RDEV 1
#define HAVE_ST_RDEV 1
#define GETGROUPS_T int
#define RETSIGTYPE void
#define HAVE_ALLOCA 1
#define HAVE_DUP2 1
#define HAVE_MEMCMP 1
#define HAVE_MEMMOVE 1
#define HAVE_MKDIR 1
#define HAVE_STRCASECMP 1
#define HAVE_STRNCASECMP 1
#define HAVE_STRERROR 1
#define HAVE_STRFTIME 1
#define HAVE_STRCHR 1
#define HAVE_STRSTR 1
#define HAVE_STRTOD 1
#define HAVE_STRTOL 1
#define HAVE_STRTOUL 1
#define HAVE_FLOCK 1
#define HAVE_VSNPRINTF 1
#define HAVE_ISNAN 1
#define HAVE_FINITE 1
#define HAVE_HYPOT 1
#define HAVE_FMOD 1
#define HAVE_FREXP 1
#define HAVE_MODF 1
#define HAVE_WAITPID 1
#define HAVE_FSYNC 1
#define HAVE_GETCWD 1
#define HAVE_CHSIZE 1
#define HAVE_TIMES 1
#define HAVE_FCNTL 1
#define HAVE__SETJMP 1
#define HAVE_TELLDIR 1
#define HAVE_SEEKDIR 1
#define HAVE_MKTIME 1
#define HAVE_COSH 1
#define HAVE_SINH 1
#define HAVE_TANH 1
// #define HAVE_TZNAME 1
// #define HAVE_DAYLIGHT 1
#define SETPGRP_VOID 1
#define RSHIFT(x,y) ((x)>>(int)y)
// #define FILE_COUNT _cnt
// #define FILE_READPTR _ptr
#define inline __inline
#define NEED_IO_SEEK_BETWEEN_RW 1
#define STACK_GROW_DIRECTION -1
#define DEFAULT_KCODE KCODE_NONE
#define DLEXT ".so"
#define DLEXT2 ".dll"

#endif

#if defined(__APPLE__) || defined(MACOSX)

/* MAC OS X version */
#define PACKAGE_NAME ""
#define PACKAGE_TARNAME ""
#define PACKAGE_VERSION ""
#define PACKAGE_STRING ""
#define PACKAGE_BUGREPORT ""
#define STDC_HEADERS 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_MEMORY_H 1
#define HAVE_STRINGS_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_STDINT_H 1
#define HAVE_UNISTD_H 1
#define HAVE_LONG_LONG 1
#define HAVE_OFF_T 1
#define SIZEOF_INT 4
#define SIZEOF_SHORT 2
#define SIZEOF_LONG 4
#define SIZEOF_LONG_LONG 8
#define SIZEOF___INT64 0
#define SIZEOF_OFF_T 8
#define SIZEOF_VOIDP 4
#define SIZEOF_FLOAT 4
#define SIZEOF_DOUBLE 8
#define SIZEOF_TIME_T 4
#define rb_pid_t pid_t
#define rb_gid_t gid_t
#define rb_uid_t uid_t
#define HAVE_PROTOTYPES 1
#define TOKEN_PASTE(x,y) x##y
#define HAVE_STDARG_PROTOTYPES 1
#define NORETURN(x) x __attribute__ ((noreturn))
#define HAVE_DECL_SYS_NERR 1
#define HAVE_LIBDL 1
#define HAVE_DIRENT_H 1
#define STDC_HEADERS 1
#define HAVE_SYS_WAIT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_UNISTD_H 1
#define HAVE_LIMITS_H 1
#define HAVE_SYS_FILE_H 1
#define HAVE_SYS_IOCTL_H 1
#define HAVE_SYS_SYSCALL_H 1
#define HAVE_FCNTL_H 1
#define HAVE_SYS_FCNTL_H 1
#define HAVE_SYS_SELECT_H 1
#define HAVE_SYS_TIME_H 1
#define HAVE_SYS_TIMES_H 1
#define HAVE_SYS_PARAM_H 1
#define HAVE_PWD_H 1
#define HAVE_GRP_H 1
#define HAVE_UTIME_H 1
#define HAVE_MEMORY_H 1
#define HAVE_SYS_RESOURCE_H 1
#define HAVE_NETINET_IN_SYSTM_H 1
#define HAVE_FLOAT_H 1
#define HAVE_PTHREAD_H 1
#define HAVE_UCONTEXT_H 1
#define HAVE_STRUCT_STAT_ST_BLKSIZE 1
#define HAVE_ST_BLKSIZE 1
#define HAVE_STRUCT_STAT_ST_BLOCKS 1
#define HAVE_ST_BLOCKS 1
#define HAVE_STRUCT_STAT_ST_RDEV 1
#define HAVE_ST_RDEV 1
#define GETGROUPS_T gid_t
#define RETSIGTYPE void
#define HAVE_FSEEKO 1
#define HAVE_FTELLO 1
#define HAVE_DUP2 1
#define HAVE_MEMMOVE 1
#define HAVE_STRCASECMP 1
#define HAVE_STRNCASECMP 1
#define HAVE_STRERROR 1
#define HAVE_STRFTIME 1
#define HAVE_STRCHR 1
#define HAVE_STRSTR 1
#define HAVE_STRTOUL 1
#define HAVE_CRYPT 1
#define HAVE_FLOCK 1
#define HAVE_VSNPRINTF 1
#define HAVE_ISNAN 1
#define HAVE_FINITE 1
#define HAVE_ISINF 1
#define HAVE_HYPOT 1
#define HAVE_ACOSH 1
#define HAVE_ERF 1
#define HAVE_FMOD 1
#define HAVE_KILLPG 1
#define HAVE_WAIT4 1
#define HAVE_WAITPID 1
#define HAVE_SYSCALL 1
#define HAVE_CHROOT 1
#define HAVE_FSYNC 1
#define HAVE_GETCWD 1
#define HAVE_TRUNCATE 1
#define HAVE_TIMES 1
#define HAVE_UTIMES 1
#define HAVE_FCNTL 1
#define HAVE_LOCKF 1
#define HAVE_LSTAT 1
#define HAVE_SYMLINK 1
#define HAVE_LINK 1
#define HAVE_READLINK 1
#define HAVE_SETITIMER 1
#define HAVE_PAUSE 1
#define HAVE_GETPGRP 1
#define HAVE_SETPGRP 1
#define HAVE_GETPGID 1
#define HAVE_SETPGID 1
#define HAVE_INITGROUPS 1
#define HAVE_GETGROUPS 1
#define HAVE_SETGROUPS 1
#define HAVE_GETPRIORITY 1
#define HAVE_GETRLIMIT 1
#define HAVE_DLOPEN 1
#define HAVE_SIGPROCMASK 1
#define HAVE_SIGACTION 1
#define HAVE__SETJMP 1
#define HAVE_SETSID 1
#define HAVE_TELLDIR 1
#define HAVE_SEEKDIR 1
#define HAVE_FCHMOD 1
#define HAVE_MKTIME 1
#define HAVE_TIMEGM 1
#define HAVE_COSH 1
#define HAVE_SINH 1
#define HAVE_TANH 1
#define HAVE_SETUID 1
#define HAVE_SETGID 1
#define HAVE_STRUCT_TM_TM_ZONE 1
#define HAVE_TM_ZONE 1
#define HAVE_STRUCT_TM_TM_GMTOFF 1
#define HAVE_DAYLIGHT 1
#define NEGATIVE_TIME_T 1
// #define POSIX_SIGNAL 1
#define GETPGRP_VOID 1
#ifdef __BIGENDIAN__
#define WORDS_BIGENDIAN 1
#endif
#define RSHIFT(x,y) ((x)>>(int)y)
#define FILE_COUNT _r
#define FILE_READPTR _p
#define NEED_IO_SEEK_BETWEEN_RW 1
#define STACK_GROW_DIRECTION -1
#define _REENTRANT 1
#define _THREAD_SAFE 1
#define HAVE_LIBPTHREAD 1
#define HAVE_NANOSLEEP 1
#define DEFAULT_KCODE KCODE_NONE
#define DLEXT ".bundle"

#else

#ifndef WIN32
/* X11 configuration.  Use the top level config.h */
#include "../../config.h"

#define GETGROUPS_T int

#define HAVE_STDARG_PROTOTYPES 1
#define TOKEN_PASTE(x,y) x##y
#define DLEXT ".so"
#define RSHIFT(x,y) ((x)>>(int)y)
#endif
#endif

/* Common definitions */

#define RUBY_PLATFORM "unknown-unknown"

#ifndef NDEBUG

/* Debugging version has access to libraries for testing */
#define RUBY_LIB "/usr/local/lib/ruby/1.8"
#define RUBY_SITE_LIB "/usr/local/lib/ruby/site_ruby"
#define RUBY_SITE_LIB2 "/usr/local/lib/ruby/site_ruby/1.8"
#define RUBY_ARCHLIB "/usr/local/lib/ruby/1.8/powerpc-darwin8.6.0"
#define RUBY_SITE_ARCHLIB "/usr/local/lib/ruby/site_ruby/1.8/powerpc-darwin8.6.0"

#else

#define RUBY_LIB ""
#define RUBY_SITE_LIB ""
#define RUBY_SITE_LIB2 ""
#define RUBY_ARCHLIB ""
#define RUBY_SITE_ARCHLIB ""

#endif
