//%includeGuardStart {
#ifndef INFERNALSPACEPOINT_H
#define INFERNALSPACEPOINT_H
//%includeGuardStart } 24fzg75iRENTffZiCr1OOg
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalSpacePoint.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } AE6fh4OKVYRKEno4yT42xQ
/*
 * $Id: InfernalSpacePoint.h,v 1.1 2003/10/04 12:23:06 southa Exp $
 * $Log: InfernalSpacePoint.h,v $
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

#include "Mushcore.h"
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
