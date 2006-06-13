//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyFail.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } 0SQZFcFDmoiv6tz5ra2xUQ
/*
 * $Id: MushRubyFail.cpp,v 1.1 2006/04/20 00:22:45 southa Exp $
 * $Log: MushRubyFail.cpp,v $
 * Revision 1.1  2006/04/20 00:22:45  southa
 * Added ruby executive
 *
 */

#include "MushRubyFail.h"

#include "MushRubyIntern.h"
#include "MushRubyRuby.h"

using namespace Mushware;
using namespace std;

MushRubyFail::MushRubyFail() :
    MushcoreNonFatalFail(ExceptionInfo())
{
}

MushRubyFail::MushRubyFail(const std::string& inMessage) :
    MushcoreNonFatalFail(inMessage)
{
}

std::string
MushRubyFail::ExceptionInfo(void)
{
    ostringstream message;
    
    tRubyError lasterr = rb_gv_get("$!");
        
    tRubyValue klassStr = rb_class_path(CLASS_OF(lasterr));
    message << RSTRING(klassStr)->ptr << ": "; 
        
    tRubyValue errorStr = rb_obj_as_string(lasterr);
    message << RSTRING(errorStr)->ptr;
        
    if(!NIL_P(ruby_errinfo))
    {
        message << std::endl;
        tRubyValue ary = rb_funcall(ruby_errinfo, MushRubyIntern::backtrace(), 0);
        for (S32 i=0; i<RARRAY(ary)->len; i++)
        {
            message << "\tfrom " << RSTRING(RARRAY(ary)->ptr[i])->ptr << std::endl;
        }
    }
    return message.str();
}
