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
 * $Id: GLVector.cpp,v 1.1 2002/10/07 17:49:45 southa Exp $
 * $Log: GLVector.cpp,v $
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
    inOut << inPrefix << "<offset>" << x << "," << y << "," << z << "</offset>" << endl;
}

void
GLVector::Unpickle(CoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for offset.  Should be <offset>10,10,30</offset>";
    char comma;
    if (!(data >> x)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);

    if (!(data >> y)) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);

    if (!(data >> z)) inXML.Throw(failMessage);
}