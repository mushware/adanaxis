//%includeGuardStart {
#ifndef MUSHRUBYEXEC_H
#define MUSHRUBYEXEC_H
//%includeGuardStart } jj9xhEoAJK7VgfefCzujZQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyExec.h
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
//%Header } TZ2iQrHfZrtYCEer1E33cg
/*
 * $Id: MushRubyExec.h,v 1.8 2007/04/18 09:23:02 southa Exp $
 * $Log: MushRubyExec.h,v $
 * Revision 1.8  2007/04/18 09:23:02  southa
 * Header and level fixes
 *
 * Revision 1.7  2006/07/28 11:14:29  southa
 * Records for multiple spaces
 *
 * Revision 1.6  2006/07/08 16:06:00  southa
 * Ruby menus and key handling
 *
 * Revision 1.5  2006/07/04 16:55:28  southa
 * Ruby key handling
 *
 * Revision 1.4  2006/06/13 10:35:05  southa
 * Ruby data objects
 *
 * Revision 1.3  2006/06/12 11:59:40  southa
 * Ruby wrapper for MushMeshVector
 *
 * Revision 1.2  2006/06/06 17:58:33  southa
 * Ruby texture definition
 *
 * Revision 1.1  2006/04/20 00:22:45  southa
 * Added ruby executive
 *
 */

#include "MushRubyStandard.h"

#include "MushRubyValue.h"

class MushRubyExec : public MushcoreSingleton<MushRubyExec>
{
public:
    MushRubyExec();
    MushRubyValue Eval(const std::string& inStr);
    MushRubyValue Call(const std::string& inRecv, const std::string& inFunc);
    MushRubyValue Call(const std::string& inStr);
    MushRubyValue Call(MushRubyValue inRecv, const std::string& inFunc);
    MushRubyValue Call(MushRubyValue inRecv, Mushware::tRubyID inFunc);
    MushRubyValue Call(MushRubyValue inRecv, Mushware::tRubyID inFunc,
                              MushRubyValue inArg0);
    MushRubyValue Call(MushRubyValue inRecv, Mushware::tRubyID inFunc,
                       MushRubyValue inArg0, MushRubyValue inArg1);
    MushRubyValue Call(MushRubyValue inRecv, Mushware::tRubyID inFunc,
                       MushRubyValue inArg0, MushRubyValue inArg1, MushRubyValue inArg2);
    MushRubyValue Call(MushRubyValue inRecv, Mushware::tRubyID inFunc,
                       MushRubyValue inArg0, MushRubyValue inArg1, MushRubyValue inArg2,
                       MushRubyValue inArg3);
    MushRubyValue Call(MushRubyValue inRecv, Mushware::tRubyID inFunc,
                       MushRubyValue inArg0, MushRubyValue inArg1, MushRubyValue inArg2,
                       MushRubyValue inArg3, MushRubyValue inArg4);
    void Require(const std::string& inStr);
    
protected:
    void Initialise(void);
    void ConfigSet(void);
	
    Mushware::tRubyValue WrapProtect(Mushware::tRubyValue inValue);
    
    static Mushware::tRubyValue StaticWrapProtect(Mushware::tRubyValue inValue);
    
private:
    enum
    {
        kMaxArgs = 5
    };
    
    Mushware::tRubyValue m_callReceiver;
    Mushware::tRubyID m_callFunction;
    std::vector<Mushware::tRubyValue> m_callArgs;
    Mushware::U32 m_callNumArgs;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
