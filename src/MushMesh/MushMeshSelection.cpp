//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshSelection.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } zMHQrpi25i6HaqGu6+OxUg
/*
 * $Id: MushMeshSelection.cpp,v 1.1 2003/10/20 13:05:57 southa Exp $
 * $Log: MushMeshSelection.cpp,v $
 * Revision 1.1  2003/10/20 13:05:57  southa
 * Created
 *
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
