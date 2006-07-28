//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyExec.cpp
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
//%Header } ZcziFKLJA7zY/8U6Ju48NA
/*
 * $Id: MushRubyExec.cpp,v 1.9 2006/07/08 16:06:00 southa Exp $
 * $Log: MushRubyExec.cpp,v $
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

void
MushRubyExec::Require(const std::string& inStr)
{
    Eval("require '"+inStr+"'");
}

void
MushRubyExec::ConfigSet(void)
{
	tRubyValue configHash = rb_hash_new();
	
	rb_hash_aset(configHash, rb_str_new2("APPLPATH"), rb_str_new2(MushcoreEnv::Sgl().VariableGet("APPLPATH").StringGet().c_str()));					   
	
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
    ruby_script("init.rb");
    
    MushcoreScalar rubyPath;
    if (MushcoreEnv::Sgl().VariableGetIfExists(rubyPath, "RUBY_PATH"))
    {
        Eval("$LOAD_PATH.push('"+rubyPath.StringGet()+"')");
        Eval("$LOAD_PATH.push('"+rubyPath.StringGet()+"/../mushruby')");
    }
    rb_set_safe_level(2);
    MushRubyInstall::Sgl().Execute();

    Require("init.rb");
}
