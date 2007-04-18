//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPiece.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } m/ZB/9lCg5hxJ2djEDwcGg
/*
 * $Id: AdanaxisPiece.cpp,v 1.1 2006/10/30 17:03:50 southa Exp $
 * $Log: AdanaxisPiece.cpp,v $
 * Revision 1.1  2006/10/30 17:03:50  southa
 * Remnants creation
 *
 */

#include "AdanaxisPiece.h"

Mushware::tRubyValue AdanaxisPiece::m_rubyKlass = Mushware::kRubyQnil;

using namespace Mushware;
using namespace std;

Mushware::tRubyValue
AdanaxisPiece::Klass(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
        RubyInstall();
    }
    return m_rubyKlass;
}    

void
AdanaxisPiece::RubyInstall(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
	    m_rubyKlass = MushRubyUtil::SubclassDefine("AdanaxisPiece", MushGamePiece::Klass());
    }
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(AdanaxisPiece::RubyInstall);
	}
	MushcoreInstaller install(Install);
}
