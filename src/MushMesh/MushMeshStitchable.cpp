//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshStitchable.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } J/gH6c/1gW8u07jqHybX0Q
/*
 * $Id: MushMeshStitchable.cpp,v 1.3 2004/01/02 21:13:11 southa Exp $
 * $Log: MushMeshStitchable.cpp,v $
 * Revision 1.3  2004/01/02 21:13:11  southa
 * Source conditioning
 *
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
