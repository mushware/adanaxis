//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/re.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /8EKXIsLVEh0H0qndtvxFA
/**********************************************************************

  re.h -

  $Author: nobu $
  $Date: 2003/03/04 14:12:19 $
  created at: Thu Sep 30 14:18:32 JST 1993

  Copyright (C) 1993-2003 Yukihiro Matsumoto

**********************************************************************/

#ifndef RE_H
#define RE_H

#include <sys/types.h>
#include <stdio.h>

#include "regex.h"

typedef struct re_pattern_buffer Regexp;

struct RMatch {
    struct RBasic basic;
    VALUE str;
    struct re_registers *regs;
};

#define RMATCH(obj)  (R_CAST(RMatch)(obj))

VALUE rb_reg_regcomp _((VALUE));
long rb_reg_search _((VALUE, VALUE, long, long));
VALUE rb_reg_regsub _((VALUE, VALUE, struct re_registers *));
long rb_reg_adjust_startpos _((VALUE, VALUE, long, long));
void rb_match_busy _((VALUE));
VALUE rb_reg_quote _((VALUE));

RUBY_EXTERN int ruby_ignorecase;

int rb_reg_mbclen2 _((unsigned int, VALUE));
#define mbclen2(c,re) rb_reg_mbclen2((c),(re))
#endif
