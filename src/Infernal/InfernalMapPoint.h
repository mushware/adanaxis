//%includeGuardStart {
#ifndef INFERNALMAPPOINT_H
#define INFERNALMAPPOINT_H
//%includeGuardStart } XrSDnk/tUzD1VahFrbpU9g
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalMapPoint.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /onvN1eqPFumRiKTAXm+rg
/*
 * $Id: InfernalMapPoint.h,v 1.2 2003/10/04 12:44:35 southa Exp $
 * $Log: InfernalMapPoint.h,v $
 * Revision 1.2  2003/10/04 12:44:35  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:06  southa
 * File renaming
 *
 * Revision 1.9  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:48  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.6  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.2  2002/08/01 16:47:12  southa
 * First multi-box collsion checking
 *
 * Revision 1.1  2002/07/31 16:27:16  southa
 * Collision checking work
 *
 */

#include "Mushcore.h"
#include "mushGL.h"

class InfernalSpacePoint;

class InfernalMapPoint : public GLPoint
{
public:
    InfernalMapPoint() {}
    explicit InfernalMapPoint(const GLPoint& inPoint) { x=inPoint.x; y=inPoint.y; }

private:
    InfernalMapPoint(const InfernalSpacePoint &inPoint) {} // prevent this
    InfernalMapPoint& operator=(const InfernalSpacePoint& inPoint) { return *this; } // prevent this
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
