//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlIDNull.cpp
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 8YFVDbFCrl+J7r/lkDcdzw
/*
 * $Id: MustlIDNull.cpp,v 1.5 2003/08/21 23:09:26 southa Exp $
 * $Log: MustlIDNull.cpp,v $
 * Revision 1.5  2003/08/21 23:09:26  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/07 17:13:45  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.3  2002/12/29 20:59:59  southa
 * More build fixes
 *
 * Revision 1.2  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.1  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 */

#include "MustlIDNull.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

using namespace Mustl;
using namespace std;

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
