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
 * $Id: MustlID.cpp,v 1.2 2002/12/17 12:53:33 southa Exp $
 * $Log: MustlID.cpp,v $
 * Revision 1.2  2002/12/17 12:53:33  southa
 * Mustl library
 *
 */

#include "MustlID.h"

using namespace Mustl;

ostream&
operator<<(ostream &ioOut, const MustlID& inObj)
{
    inObj.Print(ioOut);
    return ioOut;
}
