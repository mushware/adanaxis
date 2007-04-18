//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshGroup.cpp
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
//%Header } 0Ky/aj2P4I32jCb6+B/qrQ
/*
 * $Id: MushMeshGroup.cpp,v 1.3 2006/06/01 15:39:29 southa Exp $
 * $Log: MushMeshGroup.cpp,v $
 * Revision 1.3  2006/06/01 15:39:29  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/05/19 13:02:10  southa
 * Mac release work
 *
 * Revision 1.1  2005/01/26 00:48:46  southa
 * MushMeshGroup and rendering
 *
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
