/*
 * $Id: GameSolidMap.cpp,v 1.1 2002/07/16 17:48:08 southa Exp $
 * $Log: GameSolidMap.cpp,v $
 * Revision 1.1  2002/07/16 17:48:08  southa
 * Collision and optimisation work
 *
 */

#include "GameSolidMap.h"

#include "mushGL.h"

#include "GameMapArea.h"

void
GameSolidMap::SizeSet(U32 inXSize, U32 inYSize)
{
    m_xsize=inXSize;
    m_ysize=inYSize;
    m_solidMap.resize(0);
    m_solidMap.resize(m_xsize*m_ysize);
}
    
void
GameSolidMap::PermeabilitySet(tVal inValue, U32 inX, U32 inY)
{
    COREASSERT(inX < m_xsize);
    COREASSERT(inY < m_ysize);
    m_solidMap[m_xsize * inY + inX] = inValue;
}

tVal
GameSolidMap::PermeabilityGet(U32 inX, U32 inY) const
{
    COREASSERT(inX < m_xsize);
    COREASSERT(inY < m_ysize);
    return m_solidMap[m_xsize * inY + inX];
}

tVal
GameSolidMap::PermeabilityGet(const GLPoint& inPoint) const
{
    // Permeability is always 0 outside of the map
    if (inPoint.x < 0 || inPoint.y < 0) return 0;
    U32 x=static_cast<U32>(inPoint.x+0.5);
    U32 y=static_cast<U32>(inPoint.y+0.5);
    if (x >= m_xsize || y>= m_ysize) return 0;
    return m_solidMap[m_xsize * y + x];
}

void
GameSolidMap::TrimVector(GLPoint& ioVec, const GLPoint& inStart) const
{
    GLPoint destPoint=inStart+ioVec;
    if (PermeabilityGet(destPoint) == 0)
    {
        ioVec=GLPoint(0,0);
    }
}

void
GameSolidMap::RenderCollisionSet(const GLRectangle& inRect, tVal inAngle)
{
    GLQuad quad(inRect);
    quad.RotateAboutCentre(inAngle);
}

void
GameSolidMap::Render(const GameMapArea& inArea, const GLPoint& inSteps) const
{
    GLUtils gl;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gl.SetPosition(0,0);
    GLUtils::Scale(inSteps.x, inSteps.y, 1);
    GLPoint minPoint=inArea.MinPointGet();
    GLPoint maxPoint=inArea.MaxPointGet();

    GLRectangle wholeMap(0, 0, m_xsize, m_ysize);
    wholeMap.ConstrainPoint(minPoint);
    wholeMap.ConstrainPoint(maxPoint);

    minPoint.MakeInteger();
    maxPoint.MakeInteger();

    GLPoint point;

    for (point.x=minPoint.x; point.x<maxPoint.x; ++point.x)
    {
        for (point.y=minPoint.y; point.y<maxPoint.y; ++point.y)
        {
            if (inArea.IsWithin(point))
            {
                tVal perm=PermeabilityGet(point.U32XGet(), point.U32YGet());
                GLUtils::SetColour(0.5+0.5*cos(perm*M_PI),
                                   0.5-0.5*cos(perm*M_PI),
                                   (perm>1)?1:0);
                GLLine line((point-GLPoint(0.4, 0.4)),
                            (point+GLPoint(0.4, 0.4)));

                line.Render();
                line.RotateAboutCentre(M_PI/2);
                line.Render();
            }
        }
    }
    glPopMatrix();
}

    