/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MustlData.cpp,v 1.6 2002/12/29 20:59:58 southa Exp $
 * $Log: MustlData.cpp,v $
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
