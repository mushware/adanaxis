/*
 * $Id$
 * $Log$
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
    U32 size=ioData.BytePop();
    for (U32 i=0; i<size; ++i)
    {
        m_name += ioData.BytePop();
    }
}

void
MediaNetIDString::Print(ostream& ioOut) const
{
    ioOut << m_name;
}
