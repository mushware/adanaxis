//%includeGuardStart {
#ifndef MUSHRUBYEXEC_H
#define MUSHRUBYEXEC_H
//%includeGuardStart } jj9xhEoAJK7VgfefCzujZQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyExec.h
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
//%Header } UpB+98ShDY+5JMJVLGBArQ
/*
 * $Id: MushRubyExec.h,v 1.1 2006/04/20 00:22:45 southa Exp $
 * $Log: MushRubyExec.h,v $
 * Revision 1.1  2006/04/20 00:22:45  southa
 * Added ruby executive
 *
 */

#include "MushRubyStandard.h"

extern "C"
{
#include "ruby.h"
}

class MushRubyExec : public MushcoreSingleton<MushRubyExec>
{
public:
    MushRubyExec();
    Mushware::tRubyValue Eval(const std::string& inStr);
    Mushware::tRubyValue Call(const std::string& inRecv, const std::string& inFunc);
    Mushware::tRubyValue Call(const std::string& inStr);
    Mushware::tRubyValue Call(Mushware::tRubyValue inRecv,  const std::string& inFunc);
    void Require(const std::string& inStr);
    
protected:
    void Initialise(void);
    void ConfigSet(void);
	
    Mushware::tRubyValue WrapProtect(Mushware::tRubyValue inValue);
    
    static Mushware::tRubyValue StaticWrapProtect(Mushware::tRubyValue inValue);
    
private:
    Mushware::tRubyValue m_callReceiver;
    Mushware::tRubyID m_callFunction;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
