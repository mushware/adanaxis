//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshStitchable.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } cgkurVQvJSG+i4UxM82uig
/*
 * $Id: MushMeshStitchable.cpp,v 1.2 2003/10/19 15:59:34 southa Exp $
 * $Log: MushMeshStitchable.cpp,v $
 * Revision 1.2  2003/10/19 15:59:34  southa
 * Edge manipulation
 *
 * Revision 1.1  2003/10/19 12:41:42  southa
 * Connectors
 *
 */

#include "MushMeshStitchable.h"
//%outOfLineFunctions {
void
MushMeshStitchable::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "selection=" << m_selection;
    ioOut << "]";
}
//%outOfLineFunctions } h3Onb/ckx809sIFDZYadyA
