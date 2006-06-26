//%includeGuardStart {
#ifndef DIR_H
#define DIR_H
//%includeGuardStart } vGvEfR4iIGTZHy4P6/b9Lg
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/win32/dir.h (ruby)
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
//%Header } u7uri1nZcnc3ped8BYL0AQ
#ifdef __BORLANDC__
#  ifndef WIN32_DIR_H_
#    define WIN32_DIR_H_
#    include <sys/types.h>
#  endif
#endif

struct direct
{
    long d_namlen;
    ino_t d_ino;
    char d_name[256];
};
typedef struct {
    char *start;
    char *curr;
    long size;
    long nfiles;
    struct direct dirstr;
} DIR;


DIR*           rb_w32_opendir(const char*);
struct direct* rb_w32_readdir(DIR *);
long           rb_w32_telldir(DIR *);
void           rb_w32_seekdir(DIR *, long);
void           rb_w32_rewinddir(DIR *);
void           rb_w32_closedir(DIR *);

#define opendir   rb_w32_opendir
#define readdir   rb_w32_readdir
#define telldir   rb_w32_telldir
#define seekdir   rb_w32_seekdir
#define rewinddir rb_w32_rewinddir
#define closedir  rb_w32_closedir
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
