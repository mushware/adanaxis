//%includeGuardStart {
#ifndef INFERNALSPACEPOINT_H
#define INFERNALSPACEPOINT_H
//%includeGuardStart } 24fzg75iRENTffZiCr1OOg
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalSpacePoint.h
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
//%Header } w0YSesIfzX2yyD2kJ/K7Wg
/*
 * $Id: InfernalSpacePoint.h,v 1.6 2006/06/01 15:39:05 southa Exp $
 * $Log: InfernalSpacePoint.h,v $
 * Revision 1.6  2006/06/01 15:39:05  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:06  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/04 12:44:36  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:06  southa
 * File renaming
 *
 * Revision 1.9  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:55  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.6  2002/12/20 13:17:43  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:26  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.2  2002/08/01 16:47:12  southa
 * First multi-box collsion checking
 *
 * Revision 1.1  2002/07/31 16:27:17  southa
 * Collision checking work
 *
 */

#include "mushMushcore.h"
#include "mushGL.h"

class InfernalSpacePoint : public GLPoint
{
public:
    InfernalSpacePoint() {}
    explicit InfernalSpacePoint(const GLPoint& inPoint) { x=inPoint.x; y=inPoint.y; }

private:
    InfernalSpacePoint(const InfernalMapPoint &inPoint) {} // prevent this
    InfernalSpacePoint& operator=(const InfernalMapPoint& inPoint) { return *this; } // prevent this
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
