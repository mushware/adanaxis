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
 * $Id: GLVector.cpp,v 1.4 2002/10/22 20:42:02 southa Exp $
 * $Log: GLVector.cpp,v $
 * Revision 1.4  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.3  2002/10/12 11:22:21  southa
 * GraphicModel work
 *
 * Revision 1.2  2002/10/08 21:44:09  southa
 * 3D maps
 *
 * Revision 1.1  2002/10/07 17:49:45  southa
 * Multiple values per map element
 *
 */

#include "GLVector.h"
#include "GLUtils.h"

using namespace Mushware;

void
GLVector::Render(void) const
{
    glBegin(GL_POINTS);
    GLUtils::Vertex(x, y, z);
    glEnd();
}


void
GLVector::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << x << "," << y << "," << z;
}

void
GLVector::Unpickle(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    Unpickle(data);
}

void
GLVector::Unpickle(istream& ioIn)
{
    const char *failMessage="Bad format for vector.  Should be 10,10,30";
    char comma;
    if (!(ioIn >> x)) throw(SyntaxFail(failMessage));
    if (!(ioIn >> comma) || comma != ',') throw(SyntaxFail(failMessage));

    if (!(ioIn >> y)) throw(SyntaxFail(failMessage));
    if (!(ioIn >> comma) || comma != ',') throw(SyntaxFail(failMessage));

    if (!(ioIn >> z)) throw(SyntaxFail(failMessage));
}
