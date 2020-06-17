//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/re.h (ruby)
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
//%Header } AZb/MQvWXLEYx6qJWiAMoQ
/**********************************************************************

  re.h -

 
  $Date: 2006/04/11 23:30:10 $
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
