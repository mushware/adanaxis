/*
 * $Id: MustlData.cpp,v 1.5 2002/11/23 14:39:06 southa Exp $
 * $Log: MustlData.cpp,v $
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

#include "MustlUtils.h"

#include "mushPlatform.h"

ostream& operator<<(ostream &inOut, const MustlData& inData)
{
    inData.Print(inOut);
    return inOut;
}

void
MustlData::Print(ostream& ioOut) const
{
    ioOut << "[data size=" << m_data.size() << ", readPos=" << m_readPos << ", writePos=" << m_writePos;
    ioOut << ", messagePos=" << m_messagePos << ", sourceHost=";
    if (m_sourceValid)
    {
        ioOut<< MustlUtils::IPAddressToString(m_sourceHost) << ":" << PlatformNet::NetworkToHostOrderU16(m_sourcePort);
    }
    else
    {
        ioOut << "invalid";
    }
    ioOut << ", unpackState=" << m_unpackState << ", data='";
    for (U32 i=0; i<m_data.size() && i<m_writePos; ++i)
    {
        if (isprint(m_data[i]))
        {
            ioOut << static_cast<char>(m_data[i]);
        }
        else
        {
            ioOut << "[" << hex << static_cast<U32>(m_data[i]) << dec << "]";
        }
    }
    ioOut << "']";
}
