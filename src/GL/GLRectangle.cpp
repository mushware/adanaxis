/*
 * $Id$
 * $Log$
 */

#include "GLRectangle.h"
#include "GLPoint.h"

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
GLRectangle::FixUp(void)
{
    if (xmin > xmax) swap(xmin, xmax);
    if (ymin > ymax) swap(ymin, ymax);
}
