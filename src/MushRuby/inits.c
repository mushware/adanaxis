//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/inits.c (ruby)
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
//%Header } IFJWDI9EotuCgB6EFtYntA
/**********************************************************************

  inits.c -

 
  $Date: 2006/04/11 23:30:09 $
  created at: Tue Dec 28 16:01:58 JST 1993

  Copyright (C) 1993-2003 Yukihiro Matsumoto

**********************************************************************/

#include "ruby.h"

void Init_Array _((void));
void Init_Bignum _((void));
void Init_Binding _((void));
void Init_Comparable _((void));
void Init_Dir _((void));
void Init_Enumerable _((void));
void Init_Exception _((void));
void Init_syserr _((void));
void Init_eval _((void));
void Init_load _((void));
void Init_Proc _((void));
void Init_Thread _((void));
void Init_File _((void));
void Init_GC _((void));
void Init_Hash _((void));
void Init_IO _((void));
void Init_Math _((void));
void Init_marshal _((void));
void Init_Numeric _((void));
void Init_Object _((void));
void Init_pack _((void));
void Init_Precision _((void));
void Init_sym _((void));
void Init_process _((void));
void Init_Random _((void));
void Init_Range _((void));
void Init_Regexp _((void));
void Init_signal _((void));
void Init_String _((void));
void Init_Struct _((void));
void Init_Time _((void));
void Init_var_tables _((void));
void Init_version _((void));

void
rb_call_inits()
{
    Init_sym();
    Init_var_tables();
    Init_Object();
    Init_Comparable();
    Init_Enumerable();
    Init_Precision();
    Init_eval();
    Init_String();
    Init_Exception();
    Init_Thread();
    Init_Numeric();
    Init_Bignum();
    Init_syserr();
    Init_Array();
    Init_Hash();
    Init_Struct();
    Init_Regexp();
    Init_pack();
    Init_Range();
    Init_IO();
    Init_Dir();
    Init_Time();
    Init_Random();
    Init_signal();
    Init_process();
    Init_load();
    Init_Proc();
    Init_Binding();
    Init_Math();
    Init_GC();
    Init_marshal();
    Init_version();
}
