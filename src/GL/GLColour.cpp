//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLColour.cpp
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
//%Header } f5EGOrPwId1hR2p+XmbMxg
/*
 * $Id: GLColour.cpp,v 1.17 2006/06/01 15:38:50 southa Exp $
 * $Log: GLColour.cpp,v $
 * Revision 1.17  2006/06/01 15:38:50  southa
 * DrawArray verification and fixes
 *
 * Revision 1.16  2005/05/19 13:01:58  southa
 * Mac release work
 *
 * Revision 1.15  2004/01/02 21:13:04  southa
 * Source conditioning
 *
 * Revision 1.14  2003/10/04 15:32:08  southa
 * Module split
 *
 * Revision 1.13  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:19  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/01/13 14:31:54  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.10  2003/01/09 14:56:57  southa
 * Created Mushcore
 *
 * Revision 1.9  2003/01/07 17:13:40  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.8  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.7  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.5  2002/10/10 22:47:57  southa
 * Full light definitions
 *
 * Revision 1.4  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/09 17:09:02  southa
 * InfernalDialogue added
 *
 * Revision 1.2  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 */

#include "GLColour.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

void
GLColour::Pickle(ostream& inOut, const string& inPrefix) const
{
    inOut << inPrefix << "<colour>" << m_col[0] << "," << m_col[1] << "," << m_col[2] << "," << m_col[3] << "</colour>" << endl;
}

void
GLColour::Unpickle(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for colour.  Should be <colour>0.1,0.4,0.6,1.0</colour>";
    char comma;
    if (!(data >> m_col[0])) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);

    if (!(data >> m_col[1])) inXML.Throw(failMessage);
    if (!(data >> comma) || comma != ',') inXML.Throw(failMessage);

    if (!(data >> m_col[2])) inXML.Throw(failMessage);
    
    // We don't care if alpha isn't present
    m_col[3]=1.0;
    if ((data >> comma) && comma == ',')
    {
        data >> m_col[3];
    }
}
