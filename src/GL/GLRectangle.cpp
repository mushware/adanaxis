/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLRectangle.cpp,v 1.13 2002/12/29 20:59:52 southa Exp $
 * $Log: GLRectangle.cpp,v $
 * Revision 1.13  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.12  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.10  2002/10/17 15:50:58  southa
 * Config saving, pause and quit
 *
 * Revision 1.9  2002/10/10 13:51:16  southa
 * Speed fixes and various others
 *
 * Revision 1.8  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.6  2002/08/01 16:47:10  southa
 * First multi-box collsion checking
 *
 * Revision 1.5  2002/07/23 14:10:46  southa
 * Added GameMotion
 *
 * Revision 1.4  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 * Revision 1.3  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 * Revision 1.2  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 */

#include "GLRectangle.h"
#include "GLLine.h"
#include "GLState.h"
#include "GLUtils.h"

using namespace Mushware;
using namespace std;

GLRectangle::GLRectangle(tVal inMinX, tVal inMinY, tVal inMaxX, tVal inMaxY):
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

void
GLRectangle::ConstrainPoint(GLPoint& ioPoint) const
{
    if (ioPoint.x < xmin) ioPoint.x = xmin;
    if (ioPoint.x > xmax) ioPoint.x = xmax;
    if (ioPoint.y < ymin) ioPoint.y = ymin;
    if (ioPoint.y > ymax) ioPoint.y = ymax;
}

bool
GLRectangle::IsWithin(const GLPoint& inPoint) const
{
    return (inPoint.x >= xmin &&
            inPoint.x < xmax &&
            inPoint.y >= ymin &&
            inPoint.y < ymax);
}

bool
GLRectangle::IsIntersecting(const GLLine& inLine) const
{
    GLPoint xMinYMin(xmin,ymin);
    GLPoint xMaxYMin(xmax,ymin);

    GLLine line1(xMinYMin, xMaxYMin);

    if (inLine.IsIntersecting(line1)) return true;

    GLPoint xMaxYMax(xmax,ymax);
    GLLine line2(xMaxYMin, xMaxYMax);

    if (inLine.IsIntersecting(line2)) return true;
    
    GLPoint xMinYMax(xmin,ymax);
    GLLine line3(xMaxYMax, xMinYMax);

    if (inLine.IsIntersecting(line3)) return true;

    GLLine line4(xMinYMax, xMinYMin);
    if (inLine.IsIntersecting(line4)) return true;

    return false;
}    

tVal
GLRectangle::XSize(void) const
{
    COREASSERT(xmin <= xmax);
    return xmax-xmin;
}

tVal
GLRectangle::YSize(void) const
{
    COREASSERT(ymin <= ymax);
    return ymax-ymin;
}

GLPoint
GLRectangle::Size(void) const
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

void
GLRectangle::MakeInteger(void)
{
    double temp;
    modf(xmin, &temp);
    xmin=temp;
    modf(ymin, &temp);
    ymin=temp;
    modf(xmax, &temp);
    xmax=temp;
    modf(ymax, &temp);
    ymax=temp;
}

void
GLRectangle::Expand(tVal inExpansion)
{
    xmin-=inExpansion;
    ymin-=inExpansion;
    xmax+=inExpansion;
    ymax+=inExpansion;
}

const GLRectangle&
GLRectangle::operator+=(const GLPoint& inPoint)
{
    xmin+=inPoint.x;
    ymin+=inPoint.y;
    xmax+=inPoint.x;
    ymax+=inPoint.y;
    return *this;
}


void
GLRectangle::Pickle(ostream& inOut, const string& inPrefix) const
{
    inOut << inPrefix << "<rect>" << xmin << "," << ymin << "," << xmax << "," << ymax << "</rect>" << endl;
}

void
GLRectangle::Unpickle(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for rect.  Should be <rect>10,10,30,+20</rect>";
    char comma, plus;
    if (!(data >> xmin)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);
    
    if (!(data >> ymin)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);
    
    if (!(data >> plus)) inXML.Throw(failMessage);
    if (plus != '+') data.putback(plus);
    if (!(data >> xmax)) inXML.Throw(failMessage);
    if (plus == '+') xmax += xmin;
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);
    
    if (!(data >> plus)) inXML.Throw(failMessage);
    if (plus != '+') data.putback(plus);
    if (!(data >> ymax)) inXML.Throw(failMessage);
    if (plus == '+') ymax += ymin;
}

void
GLRectangle::Render(void) const
{
    GLState::TextureDisable();
    glBegin(GL_LINE_LOOP);
    GLUtils::Vertex(xmin, ymin);
    GLUtils::Vertex(xmax, ymin);
    GLUtils::Vertex(xmax, ymax);
    GLUtils::Vertex(xmin, ymax);
    glEnd();
}

