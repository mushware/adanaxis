/*
 * $Id: MediaNetIDString.cpp,v 1.1 2002/12/07 18:32:15 southa Exp $
 * $Log: MediaNetIDString.cpp,v $
 * Revision 1.1  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 */

#include "MediaNetIDString.h"

#include "MediaNetData.h"

MediaNetIDString::MediaNetIDString(MediaNetData& ioData)
{
    Unpack(ioData);
}

MediaNetIDString::~MediaNetIDString()
{
}

MediaNetID *
MediaNetIDString::Clone(void) const
{
    return new MediaNetIDString(*this);
}

void
MediaNetIDString::Pack(MediaNetData& ioData) const
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
MediaNetIDString::Unpack(MediaNetData& ioData)
{
    m_name = "";
    U32 size=ioData.MessageBytePop();
    for (U32 i=0; i<size; ++i)
    {
        m_name += ioData.MessageBytePop();
    }
}

void
MediaNetIDString::Print(ostream& ioOut) const
{
    ioOut << m_name;
}
