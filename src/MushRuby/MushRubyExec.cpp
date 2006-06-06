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
 * $Id: MushRubyExec.cpp,v 1.2 2006/04/21 00:10:43 southa Exp $
 * $Log: MushRubyExec.cpp,v $
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
#include "MushRubySTL.h"

using namespace Mushware;

MUSHCORE_SINGLETON_INSTANCE(MushRubyExec);

MushRubyExec::MushRubyExec()
{
    MushRubyExec::Initialise();    
}

tRubyValue
MushRubyExec::Eval(const std::string& inStr)
{
    tRubyValue retVal;
    tRubyError rubyError;
    retVal = rb_eval_string_protect(inStr.c_str(), &rubyError);
    if (rubyError)
    {
        throw MushRubyFail();
    }
    return retVal;
}

tRubyValue
MushRubyExec::WrapProtect(tRubyValue inValue)
{
    tRubyValue retVal;
    
    retVal = rb_funcall(m_callReceiver, m_callFunction, 0);
    
    return retVal;
}    

tRubyValue
MushRubyExec::StaticWrapProtect(tRubyValue inValue)
{
    return MushRubyExec::Sgl().WrapProtect(inValue);
}

tRubyValue
MushRubyExec::Call(const std::string& inRecv, const std::string& inFunc)
{
    tRubyValue retVal;
    tRubyError rubyError;
    
    m_callReceiver = rb_gv_get(inRecv.c_str());
    m_callFunction = rb_intern(inFunc.c_str());
    
    retVal = rb_protect(StaticWrapProtect, 0, &rubyError);
    
    if (rubyError)
    {
        throw MushRubyFail();
    }
    return retVal;
}

tRubyValue
MushRubyExec::Call(const std::string& inStr)
{
    tRubyValue retVal;
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

Mushware::tRubyValue
MushRubyExec::Call(Mushware::tRubyValue inRecv,  const std::string& inFunc)
{
	tRubyValue retVal;
    tRubyError rubyError;
    
    m_callReceiver = inRecv;
    m_callFunction = rb_intern(inFunc.c_str());
    
    retVal = rb_protect(StaticWrapProtect, 0, &rubyError);
    
    if (rubyError)
    {
        throw MushRubyFail();
    }
    return retVal;
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
	
    rb_gv_set("$MUSHCONFIG", configHash);
}

void
MushRubyExec::Initialise(void)
{
    ruby_init();
	ConfigSet();
    ruby_script("init.rb");
    
    MushcoreScalar rubyPath;
    if (MushcoreEnv::Sgl().VariableGetIfExists(rubyPath, "RUBY_PATH"))
    {
        Eval("$LOAD_PATH.push('"+rubyPath.StringGet()+"')");
    }
    rb_set_safe_level(2);
    MushRubyInstall::Sgl().Execute();

    Require("init.rb");
}
