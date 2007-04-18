//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshStitchable.cpp
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
//%Header } /oP7mxr8MVMqCVk7/0Megw
/*
 * $Id: MushMeshStitchable.cpp,v 1.6 2006/06/01 15:39:32 southa Exp $
 * $Log: MushMeshStitchable.cpp,v $
 * Revision 1.6  2006/06/01 15:39:32  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/06/30 12:34:59  southa
 * Mesh and source conditioner work
 *
 * Revision 1.4  2005/05/19 13:02:11  southa
 * Mac release work
 *
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
    if (m_pGeometry == NULL)
    {
        ioOut << "pGeometry=NULL"  << ", ";
    }
    else
    {
        ioOut << "pGeometry=" << *m_pGeometry << ", ";
    }
    if (m_pActiveBox == NULL)
    {
        ioOut << "pActiveBox=NULL"  << ", ";
    }
    else
    {
        ioOut << "pActiveBox=" << *m_pActiveBox << ", ";
    }
    ioOut << "selection=" << m_selection;
    ioOut << "]";
}
//%outOfLineFunctions } mgYtbL6jEKzdUfbYIuOUqA
