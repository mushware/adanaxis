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
 * $Id: GLPoint.cpp,v 1.3 2002/08/27 08:56:19 southa Exp $
 * $Log: GLPoint.cpp,v $
 * Revision 1.3  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 */

#include "GLPoint.h"
#include "GLUtils.h"

void
GLPoint::Render(void) const
{
    glBegin(GL_POINTS);
    GLUtils::Vertex(x, y);
    glEnd();
}

void
GLPoint::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << x << "," << y << endl;
}

void
GLPoint::Unpickle(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    Unpickle(data);
}

void
GLPoint::Unpickle(istream& ioIn)
{
    const char *failMessage="Bad format for point.  Should be 10,10";
    char comma;
    if (!(ioIn >> x)) throw(SyntaxFail(failMessage));
    if (!(ioIn >> comma) || comma != ',') throw(SyntaxFail(failMessage));
    if (!(ioIn >> y)) throw(SyntaxFail(failMessage));
}
