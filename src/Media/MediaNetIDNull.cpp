/*
 * $Id$
 * $Log$
 */

#include "MediaNetIDNull.h"

MediaNetIDNull::~MediaNetIDNull()
{
}

MediaNetID *
MediaNetIDNull::Clone(void) const
{
    return new MediaNetIDNull(*this);
}

void
MediaNetIDNull::Pack(MediaNetData& ioData) const
{
}

void
MediaNetIDNull::Unpack(MediaNetData& ioData)
{
}

void
MediaNetIDNull::Print(ostream& ioOut) const
{
    ioOut << "Unknown";
}
