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
 * $Id: MustlFail.cpp,v 1.1 2002/12/12 18:38:24 southa Exp $
 * $Log: MustlFail.cpp,v $
 * Revision 1.1  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 */

#include "MustlFail.h"

#include "MustlSTL.h"

using namespace Mustl;

MustlFail::~MustlFail() throw()
{
}

ostream&
operator<<(ostream &ioOut, const MustlFail& inFail)
{
    return ioOut << inFail.Print();
}
