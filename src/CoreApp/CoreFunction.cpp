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
 * $Id: CoreFunction.cpp,v 1.2 2002/05/29 08:56:16 southa Exp $
 * $Log: CoreFunction.cpp,v $
 * Revision 1.2  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.1  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 */

#include "CoreFunction.h"
#include "CoreApp.h"

void
CoreFunction::Execute(void) const
{
    for (U32 i=0; i<m_commands.size(); ++i)
    {
        CoreApp::Instance().Process(m_commands[i]);
    }
}

void
CoreFunction::Print(ostream& inOut) const
{
    for (U32 i=0; i<m_commands.size(); ++i)
    {
        inOut << m_commands[i] << endl;
    }
}
