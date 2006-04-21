//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/env.h (ruby)
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
//%Header } Rfl5XQx8rRmgMoGPezubqA
/**********************************************************************

  env.h -

 
  $Date: 2006/04/11 23:30:09 $
  created at: Mon Jul 11 11:53:03 JST 1994

  Copyright (C) 1993-2003 Yukihiro Matsumoto

**********************************************************************/

#ifndef ENV_H
#define ENV_H

extern struct FRAME {
    VALUE self;
    int argc;
    VALUE *argv;
    ID last_func;
    ID orig_func;
    VALUE last_class;
    struct FRAME *prev;
    struct FRAME *tmp;
    struct RNode *node;
    int iter;
    int flags;
    unsigned long uniq;
} *ruby_frame;

void rb_gc_mark_frame _((struct FRAME *));

#define FRAME_ALLOCA 0
#define FRAME_MALLOC 1

extern struct SCOPE {
    struct RBasic super;
    ID *local_tbl;
    VALUE *local_vars;
    int flags;
} *ruby_scope;

#define SCOPE_ALLOCA  0
#define SCOPE_MALLOC  1
#define SCOPE_NOSTACK 2
#define SCOPE_DONT_RECYCLE 4

extern int ruby_in_eval;

extern VALUE ruby_class;

struct RVarmap {
    struct RBasic super;
    ID id;
    VALUE val;
    struct RVarmap *next;
};
extern struct RVarmap *ruby_dyna_vars;

#endif /* ENV_H */
