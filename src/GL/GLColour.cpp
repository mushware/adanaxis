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
 * $Id: GLColour.cpp,v 1.4 2002/08/27 08:56:18 southa Exp $
 * $Log: GLColour.cpp,v $
 * Revision 1.4  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/09 17:09:02  southa
 * GameDialogue added
 *
 * Revision 1.2  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 */

#include "GLColour.h"

void
GLColour::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<colour>" << m_col[0] << "," << m_col[1] << "," << m_col[2] << "," << m_col[3] << "</colour>" << endl;
}

void
GLColour::Unpickle(CoreXML& inXML)
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
