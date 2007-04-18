//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLVector.cpp
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } b2Nl1nmIFd5q3tPKiw+bCA
/*
 * $Id: GLVector.cpp,v 1.15 2006/06/01 15:38:55 southa Exp $
 * $Log: GLVector.cpp,v $
 * Revision 1.15  2006/06/01 15:38:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.14  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.13  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.12  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.11  2003/08/21 23:08:33  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/01/13 14:31:56  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.9  2003/01/12 17:32:51  southa
 * Mushcore work
 *
 * Revision 1.8  2003/01/09 14:56:59  southa
 * Created Mushcore
 *
 * Revision 1.7  2003/01/07 17:13:41  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.6  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.5  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
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

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

void
GLVector::Render(void) const
{
    glBegin(GL_POINTS);
    GLUtils::Vertex(x, y, z);
    glEnd();
}


void
GLVector::Pickle(ostream& inOut, const string& inPrefix) const
{
    inOut << x << "," << y << "," << z;
}

void
GLVector::Unpickle(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    Unpickle(data);
}

void
GLVector::Unpickle(istream& ioIn)
{
    const char *failMessage="Bad format for vector.  Should be 10,10,30";
    char comma;
    if (!(ioIn >> x)) throw(MushcoreSyntaxFail(failMessage));
    if (!(ioIn >> comma) || comma != ',') throw(MushcoreSyntaxFail(failMessage));

    if (!(ioIn >> y)) throw(MushcoreSyntaxFail(failMessage));
    if (!(ioIn >> comma) || comma != ',') throw(MushcoreSyntaxFail(failMessage));

    if (!(ioIn >> z)) throw(MushcoreSyntaxFail(failMessage));
}
