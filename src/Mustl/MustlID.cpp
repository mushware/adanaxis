/*
 * $Id$
 * $Log$
 */

#include "MustlID.h"

ostream&
operator<<(ostream &ioOut, const MustlID& inObj)
{
    inObj.Print(ioOut);
    return ioOut;
}
