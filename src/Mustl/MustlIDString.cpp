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
 * $Id: MustlIDString.cpp,v 1.2 2002/12/17 12:53:33 southa Exp $
 * $Log: MustlIDString.cpp,v $
 * Revision 1.2  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.2  2002/12/09 16:18:00  southa
 * Link ID transfer
 *
 * Revision 1.1  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 */

#include "MustlIDString.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

using namespace Mustl;

MustlIDString::MustlIDString(MustlData& ioData)
{
    Unpack(ioData);
}

MustlIDString::~MustlIDString()
{
}

MustlID *
MustlIDString::Clone(void) const
{
    return new MustlIDString(*this);
}

void
MustlIDString::Pack(MustlData& ioData) const
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
MustlIDString::Unpack(MustlData& ioData)
{
    m_name = "";
    U32 size=ioData.MessageBytePop();
    for (U32 i=0; i<size; ++i)
    {
        m_name += ioData.MessageBytePop();
    }
}

void
MustlIDString::Print(ostream& ioOut) const
{
    ioOut << m_name;
}
