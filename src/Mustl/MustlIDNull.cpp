/*
 * $Id: MustlIDNull.cpp,v 1.1 2002/12/07 18:32:15 southa Exp $
 * $Log: MustlIDNull.cpp,v $
 * Revision 1.1  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 */

#include "MustlIDNull.h"

MustlIDNull::~MustlIDNull()
{
}

MustlID *
MustlIDNull::Clone(void) const
{
    return new MustlIDNull(*this);
}

void
MustlIDNull::Pack(MustlData& ioData) const
{
}

void
MustlIDNull::Unpack(MustlData& ioData)
{
}

void
MustlIDNull::Print(ostream& ioOut) const
{
    ioOut << "Unknown";
}
