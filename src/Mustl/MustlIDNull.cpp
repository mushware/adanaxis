/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MustlIDNull.cpp,v 1.1 2002/12/12 14:00:25 southa Exp $
 * $Log: MustlIDNull.cpp,v $
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.1  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 */

#include "MustlIDNull.h"

using namespace Mustl;

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
