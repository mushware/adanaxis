//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshSelection.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } e65AnwcYRZiVVQCbeip4Hg
/*
 * $Id$
 * $Log$
 */

#include "MushMeshSelection.h"
//%outOfLineFunctions {
void
MushMeshSelection::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "start=" << start << ", ";
    ioOut << "stride=" << stride << ", ";
    ioOut << "size=" << size;
    ioOut << "]";
}
//%outOfLineFunctions } paTFObkZeEk2ziQvG69Lyw
