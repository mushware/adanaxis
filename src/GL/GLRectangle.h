/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GLPoint;

class GLRectangle
{
public:
    GLRectangle(tVal inMinX=0, tVal inMinY=0, tVal inMaxX=0, tVal inMaxY=0);
    GLRectangle(const GLPoint& inMin, const GLPoint& inMax);
    void FixUp(void);
    tVal xmin;
    tVal ymin;
    tVal xmax;
    tVal ymax;
};
