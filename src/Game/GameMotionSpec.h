//%includeGuardStart {
#ifndef GAMEMOTIONSPEC_H
#define GAMEMOTIONSPEC_H
//%includeGuardStart } Bh+r3AOmFE1Y0PPYZNk4eA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameMotionSpec.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } c6jaAhjKHvuTk4PguDdmng
/*
 * $Id: GameMotionSpec.h,v 1.11 2003/08/21 23:08:49 southa Exp $
 * $Log: GameMotionSpec.h,v $
 * Revision 1.11  2003/08/21 23:08:49  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.9  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/17 16:41:21  southa
 * Initialisation fix and player facet
 *
 * Revision 1.6  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/09 17:09:04  southa
 * GameDialogue added
 *
 * Revision 1.4  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.3  2002/08/05 13:37:29  southa
 * Windback work
 *
 * Revision 1.2  2002/07/23 14:10:47  southa
 * Added GameMotion
 *
 * Revision 1.1  2002/07/18 11:40:35  southa
 * Overplotting and movement
 *
 */

#include "Mushcore.h"
#include "mushGL.h"

class GameMotionSpec
{
public:
    GameMotionSpec() {}
    GameMotionSpec(const GLPoint& inPoint, Mushware::tVal inAngle);
    void Windback(Mushware::tVal inScale);
    const GameMotionSpec WindbackGet(Mushware::tVal inScale) const;
    void ApplyDelta(void);
    void Render(void) const;
    void ZeroSet(void);
    
    GLPoint pos;
    Mushware::tVal angle;
    GLRectangle shape;
    GLPoint deltaPos;
    Mushware::tVal deltaAngle;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
