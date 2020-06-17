//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLVector.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } O8muaWeojpRIbkQKb3NVeg
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
