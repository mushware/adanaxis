//%includeGuardStart {
#ifndef GAMEMAPAREA_H
#define GAMEMAPAREA_H
//%includeGuardStart } ZwdPFpmwWOQImvXeFEtjTA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameMapArea.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } +RZvsVaB+r13C5QZ2dy6XA
/*
 * $Id: GameMapArea.h,v 1.9 2003/08/21 23:08:48 southa Exp $
 * $Log: GameMapArea.h,v $
 * Revision 1.9  2003/08/21 23:08:48  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/11 17:07:52  southa
 * Mushcore library separation
 *
 * Revision 1.7  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.6  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.4  2002/10/10 13:51:17  southa
 * Speed fixes and various others
 *
 * Revision 1.3  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/16 17:48:08  southa
 * Collision and optimisation work
 *
 */

#include "Mushcore.h"
#include "mushGL.h"

class GameMapArea
{
public:
    void RectangleAdd(const GLRectangle& inRectangle);
    void CircleAdd(const GLPoint& inPoint, Mushware::tVal inRadius);
    bool IsWithin(const GLPoint& inPoint) const;
    const GLPoint MinPointGet(void) const;
    const GLPoint MaxPointGet(void) const;
    const GLRectangle BoundingBoxGet(void) const;
    bool IsEmpty(void) const;
    
private:
    std::vector<GLRectangle> m_rectangles;
    std::vector<Mushware::tVal> m_radiiSquared;
    std::vector<GLPoint> m_points;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
