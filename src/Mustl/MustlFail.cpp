/*
 * $Id$
 * $Log$
 */

#include "MustlFail.h"

#include "MustlSTL.h"

MustlFail::~MustlFail() throw()
{
}

ostream&
operator<<(ostream &ioOut, const MustlFail& inFail)
{
    return ioOut << inFail.Print();
}
