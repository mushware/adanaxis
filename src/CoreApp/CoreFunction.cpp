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
 * $Id: CoreFunction.cpp,v 1.8 2002/08/27 08:56:17 southa Exp $
 * $Log: CoreFunction.cpp,v $
 * Revision 1.8  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 * Revision 1.4  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.1  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 */

#include "CoreFunction.h"
#include "CoreApp.h"
#include "CoreException.h"

void
CoreFunction::Execute(void) const
{
    for (U32 i=0; i<m_commands.size(); ++i)
    {
        try
        {
            CoreApp::Instance().Process(m_commands[i]);
        }
        catch (CommandFail& e)
        {
            cerr << "*** Command failed: " << e.what() << endl;
        }
        catch (LoaderFail& e)
        {
            cerr << "*** Command failed: " << e.what() << endl;
        }
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
