//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLColour.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } wAiYZA5VGs61ng/mx32jig
/*
 * $Id: GLColour.cpp,v 1.13 2003/09/17 19:40:29 southa Exp $
 * $Log: GLColour.cpp,v $
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
