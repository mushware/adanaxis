/*
 * $Id: MediaNetData.cpp,v 1.3 2002/11/03 20:10:00 southa Exp $
 * $Log: MediaNetData.cpp,v $
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

#include "MediaNetData.h"

#include "MediaNetUtils.h"

ostream& operator<<(ostream &inOut, const MediaNetData& inData)
{
    inData.Print(inOut);
    return inOut;
}

void
MediaNetData::Print(ostream& ioOut) const
{
    ioOut << "[data size=" << m_data.size() << ", readPos=" << m_readPos << ", writePos=" << m_writePos;
    ioOut << ", messagePos=" << m_messagePos << ", sourceHost=";
    if (m_sourceValid)
    {
        ioOut<< MediaNetUtils::IPAddressToString(m_sourceHost) << ":" << m_sourcePort;
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
