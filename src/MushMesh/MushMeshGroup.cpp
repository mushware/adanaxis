//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshGroup.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 9VrYW1gzTlItdkT7ucn99w
/*
 * $Id$
 * $Log$
 */

#include "MushMeshGroup.h"

//%outOfLineFunctions {
void
MushMeshGroup::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "group=" << m_group;
    ioOut << "]";
}
//%outOfLineFunctions } hFZM/qFMDZz4tG4AuAlt4w
