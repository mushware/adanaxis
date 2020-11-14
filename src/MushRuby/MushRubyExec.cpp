//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyExec.cpp
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
//%Header } on2UVvSrk5J1BaUMVzNOBw
/*
 * $Id: MushRubyExec.cpp,v 1.13 2007/06/28 15:15:16 southa Exp $
 * $Log: MushRubyExec.cpp,v $
 * Revision 1.13  2007/06/28 15:15:16  southa
 * Mandriva fixes
 *
 * Revision 1.12  2007/06/14 18:55:12  southa
 * Level and display tweaks
 *
 * Revision 1.11  2007/03/13 21:45:11  southa
 * Release process
 *
 * Revision 1.10  2006/07/28 11:14:29  southa
 * Records for multiple spaces
 *
 * Revision 1.9  2006/07/08 16:06:00  southa
 * Ruby menus and key handling
 *
 * Revision 1.8  2006/07/04 16:55:28  southa
 * Ruby key handling
 *
 * Revision 1.7  2006/07/02 16:34:46  southa
 * Ruby rearrangement
 *
 * Revision 1.6  2006/07/02 09:43:28  southa
 * MushGLFont work
 *
 * Revision 1.5  2006/06/13 10:35:05  southa
 * Ruby data objects
 *
 * Revision 1.4  2006/06/12 11:59:40  southa
 * Ruby wrapper for MushMeshVector
 *
 * Revision 1.3  2006/06/06 17:58:33  southa
 * Ruby texture definition
 *
 * Revision 1.2  2006/04/21 00:10:43  southa
 * MushGLFont ruby module
 *
 * Revision 1.1  2006/04/20 00:22:45  southa
 * Added ruby executive
 *
 */

#include "MushRubyExec.h"

#include "MushRubyFail.h"
#include "MushRubyInstall.h"
#include "MushRubyIntern.h"
#include "MushRubyRuby.h"
#include "MushRubySTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushRubyExec);

MushRubyExec::MushRubyExec() :
    m_callArgs(kMaxArgs),
    m_callNumArgs(0)
{
    MushRubyExec::Initialise();    
}

MushRubyValue
MushRubyExec::Eval(const std::string& inStr)
{
    tRubyValue retVal;
    tRubyError rubyError;
    retVal = rb_eval_string_protect(inStr.c_str(), &rubyError);
    if (rubyError)
    {
        throw MushRubyFail();
    }
    return MushRubyValue(retVal);
}

tRubyValue
MushRubyExec::WrapProtect(tRubyValue inValue)
{
    tRubyValue retVal;
    
    retVal = rb_funcall3(m_callReceiver, m_callFunction, m_callNumArgs, &m_callArgs[0]);
    
    return retVal;
}    

tRubyValue
MushRubyExec::StaticWrapProtect(tRubyValue inValue)
{
    return MushRubyExec::Sgl().WrapProtect(inValue);
}

MushRubyValue
MushRubyExec::Call(const std::string& inRecv, const std::string& inFunc)
{
    tRubyValue retVal;
    tRubyError rubyError;
    
    m_callReceiver = rb_gv_get(inRecv.c_str());
    m_callFunction = rb_intern(inFunc.c_str());
    m_callNumArgs = 0;
    
    retVal = rb_protect(StaticWrapProtect, 0, &rubyError);
    
    if (rubyError)
    {
        throw MushRubyFail();
    }
    return MushRubyValue(retVal);
}

MushRubyValue
MushRubyExec::Call(const std::string& inStr)
{
    MushRubyValue retVal;
    U32 dotPos = inStr.find(".", 0);
    
    if (dotPos == inStr.npos)
    {
        retVal = Call("Kernel", inStr);  
    }
    else
    {
        retVal = Call(inStr.substr(0, dotPos), inStr.substr(dotPos+1, inStr.npos));
    }
    return retVal;
}    

MushRubyValue
MushRubyExec::Call(MushRubyValue inRecv,  const std::string& inFunc)
{
	tRubyValue retVal;
    tRubyError rubyError;
    
    m_callReceiver = inRecv.Value();
    m_callFunction = rb_intern(inFunc.c_str());
    m_callNumArgs = 0;
    
    retVal = rb_protect(StaticWrapProtect, 0, &rubyError);
    
    if (rubyError)
    {
        throw MushRubyFail();
    }
    return MushRubyValue(retVal);
}

MushRubyValue
MushRubyExec::Call(MushRubyValue inRecv,  Mushware::tRubyID inFunc)
{
	tRubyValue retVal;
    tRubyError rubyError;
    
    m_callReceiver = inRecv.Value();
    m_callFunction = inFunc;
    m_callNumArgs = 0;
    
    retVal = rb_protect(StaticWrapProtect, 0, &rubyError);
    
    if (rubyError)
    {
        throw MushRubyFail();
    }
    return MushRubyValue(retVal);
}

MushRubyValue
MushRubyExec::Call(MushRubyValue inRecv, Mushware::tRubyID inFunc,
                   MushRubyValue inArg0)
{
	tRubyValue retVal;
    tRubyError rubyError;
    
    m_callReceiver = inRecv.Value();
    m_callFunction = inFunc;
    MUSHCOREASSERT(m_callArgs.size() >= 1);
    m_callArgs[0] = inArg0.Value();
    m_callNumArgs = 1;
    
    retVal = rb_protect(StaticWrapProtect, 0, &rubyError);
    
    if (rubyError)
    {
        throw MushRubyFail();
    }
    return MushRubyValue(retVal);
}

MushRubyValue
MushRubyExec::Call(MushRubyValue inRecv, Mushware::tRubyID inFunc,
                   MushRubyValue inArg0, MushRubyValue inArg1)
{
	tRubyValue retVal;
    tRubyError rubyError;
    
    m_callReceiver = inRecv.Value();
    m_callFunction = inFunc;
    MUSHCOREASSERT(m_callArgs.size() >= 2);
    m_callArgs[0] = inArg0.Value();
    m_callArgs[1] = inArg1.Value();
    m_callNumArgs = 2;
    
    retVal = rb_protect(StaticWrapProtect, 0, &rubyError);
    
    if (rubyError)
    {
        throw MushRubyFail();
    }
    return MushRubyValue(retVal);
}

MushRubyValue
MushRubyExec::Call(MushRubyValue inRecv, Mushware::tRubyID inFunc,
                   MushRubyValue inArg0, MushRubyValue inArg1, MushRubyValue inArg2)
{
	tRubyValue retVal;
    tRubyError rubyError;
    
    m_callReceiver = inRecv.Value();
    m_callFunction = inFunc;
    MUSHCOREASSERT(m_callArgs.size() >= 3);
    m_callArgs[0] = inArg0.Value();
    m_callArgs[1] = inArg1.Value();
    m_callArgs[2] = inArg2.Value();
    m_callNumArgs = 3;
    
    retVal = rb_protect(StaticWrapProtect, 0, &rubyError);
    
    if (rubyError)
    {
        throw MushRubyFail();
    }
    return MushRubyValue(retVal);
}

MushRubyValue
MushRubyExec::Call(MushRubyValue inRecv, Mushware::tRubyID inFunc,
                   MushRubyValue inArg0, MushRubyValue inArg1, MushRubyValue inArg2,
                   MushRubyValue inArg3)
{
	tRubyValue retVal;
    tRubyError rubyError;
    
    m_callReceiver = inRecv.Value();
    m_callFunction = inFunc;
    MUSHCOREASSERT(m_callArgs.size() >= 4);
    m_callArgs[0] = inArg0.Value();
    m_callArgs[1] = inArg1.Value();
    m_callArgs[2] = inArg2.Value();
    m_callArgs[3] = inArg3.Value();
    m_callNumArgs = 4;
    
    retVal = rb_protect(StaticWrapProtect, 0, &rubyError);
    
    if (rubyError)
    {
        throw MushRubyFail();
    }
    return MushRubyValue(retVal);
}

MushRubyValue
MushRubyExec::Call(MushRubyValue inRecv, Mushware::tRubyID inFunc,
                   MushRubyValue inArg0, MushRubyValue inArg1, MushRubyValue inArg2,
                   MushRubyValue inArg3, MushRubyValue inArg4)
{
	tRubyValue retVal;
    tRubyError rubyError;
    
    m_callReceiver = inRecv.Value();
    m_callFunction = inFunc;
    MUSHCOREASSERT(m_callArgs.size() >= 5);
    m_callArgs[0] = inArg0.Value();
    m_callArgs[1] = inArg1.Value();
    m_callArgs[2] = inArg2.Value();
    m_callArgs[3] = inArg3.Value();
    m_callArgs[4] = inArg4.Value();
    m_callNumArgs = 5;
    
    retVal = rb_protect(StaticWrapProtect, 0, &rubyError);
    
    if (rubyError)
    {
        throw MushRubyFail();
    }
    return MushRubyValue(retVal);
}

void
MushRubyExec::Require(const std::string& inStr)
{
    Eval("require '"+inStr+"'");
}

void
MushRubyExec::ConfigSet(void)
{
    tRubyValue configHash = rb_hash_new();

    rb_hash_aset(configHash, rb_str_new2("RESOURCES_PATH"), rb_str_new2(MushcoreEnv::Sgl().VariableGet("RESOURCES_PATH").StringGet().c_str()));

#ifdef MUSHCORE_DEBUG
    rb_hash_aset(configHash, rb_str_new2("DEBUG"), Mushware::kRubyQtrue);
#else
    rb_hash_aset(configHash, rb_str_new2("DEBUG"), Mushware::kRubyQfalse);
#endif

    rb_gv_set("$MUSHCONFIG", configHash);
}

void
MushRubyExec::Initialise(void)
{
    ruby_init();

#ifdef MUSHCORE_DEBUG
    ruby_init_loadpath();
#endif

    MushRubyIntern::Initialise();
	
    ConfigSet();
    
    // Must have an absolute path here
    MushcoreScalar rubyPath;
    if (MushcoreEnv::Sgl().VariableGetIfExists(rubyPath, "RUBY_PATH"))
    {
        MushcoreRegExp pathExp("^(/|\\w+:/|\\\\|\\w+:\\\\)");
        if (!pathExp.Search(rubyPath.StringGet()))
        {
            MushcoreLog::Sgl().WarningLog() << "Path to ruby scripts set to '" << rubyPath.StringGet() << "' but should be absolute" << endl;
        }

        Eval("$LOAD_PATH.push('"+rubyPath.StringGet()+"')");
        Eval("$LOAD_PATH.push('"+rubyPath.StringGet()+"/../mushruby')");
        ruby_script((rubyPath.StringGet()+"/ruby/init.rb").c_str());
    }
    // rb_set_safe_level(2);
    MushRubyInstall::Sgl().Execute();
    Require("init.rb");
}
