//%includeGuardStart {
#ifndef MUSHRUBYINSTALL_H
#define MUSHRUBYINSTALL_H
//%includeGuardStart } 3UeA3jhmLesW/JpzA9vyDA
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyInstall.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } PVyT2b+AdkrmY9CbyOVubw
/*
 * $Id: MushRubyInstall.h,v 1.2 2006/06/13 19:30:39 southa Exp $
 * $Log: MushRubyInstall.h,v $
 * Revision 1.2  2006/06/13 19:30:39  southa
 * Ruby mesh generation
 *
 * Revision 1.1  2006/04/21 00:10:43  southa
 * MushGLFont ruby module
 *
 */

#include "MushRubyStandard.h"

class MushRubyInstall : public MushcoreSingleton<MushRubyInstall>
{
public:
    typedef void (*tpInstallFunction)(void);
    
    void Add(tpInstallFunction inFunction);
    void Execute(void);
private:
    
    std::vector<tpInstallFunction> m_installFunctions;
};

#define MUSHRUBY_INSTALL(a) \
namespace \
{ \
	void Install(void) \
	{ \
		MushRubyInstall::Sgl().Add(a::RubyInstall); \
	} \
	MushcoreInstaller install(Install); \
}


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
