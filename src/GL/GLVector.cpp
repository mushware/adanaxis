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
 * $Id: GLVector.cpp,v 1.2 2002/10/08 21:44:09 southa Exp $
 * $Log: GLVector.cpp,v $
 * Revision 1.2  2002/10/08 21:44:09  southa
 * 3D maps
 *
 * Revision 1.1  2002/10/07 17:49:45  southa
 * Multiple values per map element
 *
 */

#include "GLVector.h"
#include "GLUtils.h"

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