//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/version.c
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
//%Header } 2ntje/mXIPGi1EBmi78xkw
/**********************************************************************

  version.c -

  $Author: nobu $
  $Date: 2005/05/12 00:54:36 $
  created at: Thu Sep 30 20:08:01 JST 1993

  Copyright (C) 1993-2003 Yukihiro Matsumoto

**********************************************************************/

#include "ruby.h"
#include "version.h"
#include <stdio.h>

const char ruby_version[] = RUBY_VERSION;
const char ruby_release_date[] = RUBY_RELEASE_DATE;
const char ruby_platform[] = RUBY_PLATFORM;

void
Init_version()
{
    VALUE v = rb_obj_freeze(rb_str_new2(ruby_version));
    VALUE d = rb_obj_freeze(rb_str_new2(ruby_release_date));
    VALUE p = rb_obj_freeze(rb_str_new2(ruby_platform));

    rb_define_global_const("RUBY_VERSION", v);
    rb_define_global_const("RUBY_RELEASE_DATE", d);
    rb_define_global_const("RUBY_PLATFORM", p);

    /* obsolete constants */
    rb_define_global_const("VERSION", v);
    rb_define_global_const("RELEASE_DATE", d);
    rb_define_global_const("PLATFORM", p);
}

void
ruby_show_version()
{
    printf("ruby %s (%s) [%s]\n", RUBY_VERSION, RUBY_RELEASE_DATE, RUBY_PLATFORM);
    fflush(stdout);
}

void
ruby_show_copyright()
{
    printf("ruby - Copyright (C) 1993-%d Yukihiro Matsumoto\n", RUBY_RELEASE_YEAR);
    exit(0);
}
