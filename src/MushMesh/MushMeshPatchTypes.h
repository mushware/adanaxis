//%includeGuardStart {
#ifndef MUSHMESHPATCHTYPES_H
#define MUSHMESHPATCHTYPES_H
//%includeGuardStart } 61VEPjhxd/HdAqy8k7NbRA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatchTypes.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } XyohOX6QzagMqNyG670p4Q
/*
 * $Id: MushMeshPatchTypes.h,v 1.1 2003/10/19 12:41:42 southa Exp $
 * $Log: MushMeshPatchTypes.h,v $
 * Revision 1.1  2003/10/19 12:41:42  southa
 * Connectors
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshArray.h"
#include "MushMeshVector.h"

namespace Mushware
{
    enum
    {
        kMushMeshPositionOrder=3,
        kMushMeshNormalOrder=3,
        kMushMeshGeometryCoordOrder = kMushMeshPositionOrder + kMushMeshNormalOrder,
        kMushMeshTexCoordOrder=4,
    };

    typedef Mushware::tVal tGeometryCoordValue; 
    typedef Mushware::tVal tTexCoordValue;
    typedef MushMeshVector<tGeometryCoordValue, kMushMeshGeometryCoordOrder> tGeometryVector;
    typedef MushMeshArray<tGeometryVector> tGeometryArray;
    typedef MushMeshVector<tTexCoordValue, kMushMeshTexCoordOrder> tTexCoordVector;
    typedef MushMeshArray<tTexCoordVector> tTexCoordArray;
    typedef std::vector<tTexCoordArray> tTexCoordArrayVector;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
