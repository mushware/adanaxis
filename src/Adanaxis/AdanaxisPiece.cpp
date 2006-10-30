//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPiece.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 5r8bQyznw6kxTwehJ/sIEA
/*
 * $Id$
 * $Log$
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
