/*
 * $Id$
 * $Log$
 */

#include "MediaNetData.h"

ostream& operator<<(ostream &inOut, const MediaNetData& inData)
{
    inData.Print(inOut);
    return inOut;
}

void
MediaNetData::Print(ostream& ioOut) const
{
    ioOut << "[data size=" << m_data.size() << ", readPos=" << m_readPos << ", writePos=" << m_writePos << "] '";
    for (U32 i=0; i<m_data.size() && i<m_writePos; ++i)
    {
        if (isprint(m_data[i]))
        {
            ioOut << static_cast<char>(m_data[i]);
        }
        else
        {
            ioOut << "[" << hex << m_data[i] << dec << "]";
        }
    }
    ioOut << "'";
}
