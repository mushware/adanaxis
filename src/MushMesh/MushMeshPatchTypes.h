//%includeGuardStart {
#ifndef MUSHMESHPATCHTYPES_H
#define MUSHMESHPATCHTYPES_H
//%includeGuardStart } 61VEPjhxd/HdAqy8k7NbRA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatchTypes.h
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } OWwJXc9vG7aanjQ+dpGNqg
/*
 * $Id: MushMeshPatchTypes.h,v 1.4 2006/06/01 15:39:31 southa Exp $
 * $Log: MushMeshPatchTypes.h,v $
 * Revision 1.4  2006/06/01 15:39:31  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/05/19 13:02:10  southa
 * Mac release work
 *
 * Revision 1.2  2004/01/02 21:13:11  southa
 * Source conditioning
 *
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
