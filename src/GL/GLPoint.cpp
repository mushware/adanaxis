//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLPoint.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } wePmsEZIcduqIj6a0A+Yqg
/*
 * $Id: GLPoint.cpp,v 1.14 2003/09/17 19:40:29 southa Exp $
 * $Log: GLPoint.cpp,v $
 * Revision 1.14  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.13  2003/08/21 23:08:24  southa
 * Fixed file headers
 *
 * Revision 1.12  2003/01/13 14:31:54  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.11  2003/01/12 17:32:50  southa
 * Mushcore work
 *
 * Revision 1.10  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.9  2003/01/07 17:13:40  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.8  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.7  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.5  2002/10/17 15:50:58  southa
 * Config saving, pause and quit
 *
 * Revision 1.4  2002/10/12 11:22:21  southa
 * GraphicModel work
 *
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
#include "GLState.h"
#include "GLUtils.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

void
GLPoint::Render(void) const
{
    GLState::TextureDisable();
    glBegin(GL_POINTS);
    GLUtils::Vertex(x, y);
    glEnd();
}

void
GLPoint::Pickle(ostream& inOut, const string& inPrefix) const
{
    inOut << x << "," << y << endl;
}

void
GLPoint::Unpickle(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    Unpickle(data);
}

void
GLPoint::Unpickle(istream& ioIn)
{
    const char *failMessage="Bad format for point.  Should be 10,10";
    char comma;
    if (!(ioIn >> x)) throw(MushcoreSyntaxFail(failMessage));
    if (!(ioIn >> comma) || comma != ',') throw(MushcoreSyntaxFail(failMessage));
    if (!(ioIn >> y)) throw(MushcoreSyntaxFail(failMessage));
}
