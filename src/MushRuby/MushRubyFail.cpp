//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyFail.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } gg8Oe77RA7YQv7mro/LN3g
/*
 * $Id: MushRubyFail.cpp,v 1.4 2006/06/29 11:40:40 southa Exp $
 * $Log: MushRubyFail.cpp,v $
 * Revision 1.4  2006/06/29 11:40:40  southa
 * X11 and 64 bit fixes
 *
 * Revision 1.3  2006/06/23 00:35:07  southa
 * win32 build fixes
 *
 * Revision 1.2  2006/06/13 10:35:05  southa
 * Ruby data objects
 *
 * Revision 1.1  2006/04/20 00:22:45  southa
 * Added ruby executive
 *
 */

#include "MushRubyFail.h"

#include "MushRubyIntern.h"
#include "MushRubyRuby.h"
#include "MushRubySTL.h"

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
    
    tRubyValue lasterr = rb_gv_get("$!");

    tRubyValue klassStr = rb_class_path(CLASS_OF(lasterr));
    message << StringValueCStr(klassStr) << ": ";
        
    tRubyValue errorStr = rb_obj_as_string(lasterr);
    message << StringValueCStr(errorStr);
        
    if(!NIL_P(rb_errinfo()))
    {
        message << std::endl;
        tRubyValue ary = rb_funcall(rb_errinfo(), MushRubyIntern::backtrace(), 0);
        for (S32 i=0; i<RARRAY_LEN(ary); i++)
        {
            VALUE entry = rb_ary_entry(ary, i);
            message << "\tfrom " << rb_string_value_cstr(&entry) << std::endl;
        }
    }
    return message.str();
}
