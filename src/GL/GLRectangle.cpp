/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GLRectangle.cpp,v 1.1 2002/07/02 18:36:56 southa Exp $
 * $Log: GLRectangle.cpp,v $
 * Revision 1.1  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 */

#include "GLRectangle.h"

GLRectangle::GLRectangle(tVal inMinX=0, tVal inMinY=0, tVal inMaxX=0, tVal inMaxY=0):
xmin(inMinX),
ymin(inMinY),
xmax(inMaxX),
ymax(inMaxY)
{}

GLRectangle::GLRectangle(const GLPoint& inMin, const GLPoint& inMax):
xmin(inMin.x),
ymin(inMin.y),
xmax(inMax.x),
ymax(inMax.y)
{}

void
GLRectangle::Clip(const GLRectangle& inClip)
{
    if (xmin < inClip.xmin) xmin=inClip.xmin;
    if (xmin > inClip.xmax) xmin=inClip.xmax;
    if (ymin < inClip.ymin) ymin=inClip.ymin;
    if (ymin > inClip.ymax) ymin=inClip.ymax;
    if (xmax < inClip.xmin) xmax=inClip.xmin;
    if (xmax > inClip.xmax) xmax=inClip.xmax;
    if (ymax < inClip.ymin) ymax=inClip.ymin;
    if (ymax > inClip.ymax) ymax=inClip.ymax;
}

tVal
GLRectangle::XSize(void)
{
    COREASSERT(xmin <= xmax);
    return xmax-xmin;
}

tVal
GLRectangle::YSize(void)
{
    COREASSERT(ymin <= ymax);
    return ymax-ymin;
}

GLPoint
GLRectangle::Size(void)
{
    COREASSERT(xmin <= xmax && ymin <= ymax);
    return GLPoint(xmax-xmin, ymax-ymin);
}

void
GLRectangle::FixUp(void)
{
    if (xmin > xmax) swap(xmin, xmax);
    if (ymin > ymax) swap(ymin, ymax);
}
