//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlIDString.cpp
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
//%Header } ISz+GPoqp8/pKLfJDM9Ifw
/*
 * $Id: MustlIDString.cpp,v 1.8 2005/05/19 13:02:18 southa Exp $
 * $Log: MustlIDString.cpp,v $
 * Revision 1.8  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:26  southa
 * Fixed file headers
 *
 * Revision 1.4  2002/12/29 20:59:59  southa
 * More build fixes
 *
 * Revision 1.3  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.2  2002/12/09 16:18:00  southa
 * Link ID transfer
 *
 * Revision 1.1  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 */

#include "MustlIDString.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

using namespace Mustl;
using namespace std;

MustlIDString::MustlIDString(MustlData& ioData)
{
    Unpack(ioData);
}

MustlIDString::~MustlIDString()
{
}

MustlID *
MustlIDString::Clone(void) const
{
    return new MustlIDString(*this);
}

void
MustlIDString::Pack(MustlData& ioData) const
{
    U32 size=m_name.size();
    if (size > 255) size=255;
    ioData.BytePush(size);
    for (U32 i=0; i<size; ++i)
    {
        ioData.BytePush(m_name[i]);
    }
}

void
MustlIDString::Unpack(MustlData& ioData)
{
    m_name = "";
    U32 size=ioData.MessageBytePop();
    for (U32 i=0; i<size; ++i)
    {
        m_name += ioData.MessageBytePop();
    }
}

void
MustlIDString::Print(ostream& ioOut) const
{
    ioOut << m_name;
}
