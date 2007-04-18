//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlData.cpp
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
//%Header } X2cc6+LZ9kxhkVoa6P1e1Q
/*
 * $Id: MustlData.cpp,v 1.11 2006/06/01 15:39:51 southa Exp $
 * $Log: MustlData.cpp,v $
 * Revision 1.11  2006/06/01 15:39:51  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.9  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:24  southa
 * Fixed file headers
 *
 * Revision 1.6  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.5  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/12/14 15:04:33  southa
 * Mustl fixes
 *
 * Revision 1.3  2002/12/13 19:03:05  southa
 * Mustl interface cleanup
 *
 * Revision 1.2  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 * Revision 1.5  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.4  2002/11/04 01:02:38  southa
 * Link checks
 *
 * Revision 1.3  2002/11/03 20:10:00  southa
 * Initial message unpacking
 *
 * Revision 1.2  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.1  2002/11/01 16:15:27  southa
 * Network send and receive
 *
 */

#include "MustlData.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

using namespace Mustl;
using namespace std;

ostream& operator<<(ostream &inOut, const MustlData& inData)
{
    inData.Print(inOut);
    return inOut;
}

void
MustlData::Print(ostream& ioOut) const
{
    ioOut << "size=" << m_data.size() << ", readPos=" << m_readPos << ", writePos=" << m_writePos;
    ioOut << ", messagePos=" << m_messagePos << ", lengthPos=" << m_lengthPos;
    ioOut <<", sourceAddress=";
    if (m_sourceValid)
    {
        ioOut << m_sourceAddress;
    }
    else
    {
        ioOut << "invalid";
    }
    ioOut << ", unpackState=" << m_unpackState << ", data='";
    U32 size=m_data.size();
    for (U32 i=0; i < size && i < m_writePos; ++i)
    {
        if (isprint(m_data[i]) && m_data[i] != '[')
        {
            ioOut << static_cast<char>(m_data[i]);
        }
        else
        {
            ioOut << "[" << hex << static_cast<U32>(m_data[i]) << dec << "]";
        }
    }
    ioOut << "'";
}
