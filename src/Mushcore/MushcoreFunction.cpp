/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MushcoreFunction.cpp,v 1.13 2002/12/29 20:59:51 southa Exp $
 * $Log: MushcoreFunction.cpp,v $
 * Revision 1.13  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.12  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/11/17 13:38:30  southa
 * Game selection
 *
 * Revision 1.10  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.9  2002/09/07 09:54:01  southa
 * Tweaks to Mandrake RPM
 *
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

#include "MushcoreFunction.h"
#include "MushcoreApp.h"
#include "MushcoreException.h"

using namespace Mushware;
using namespace std;

void
MushcoreFunction::Execute(void) const
{
    for (U32 i=0; i<m_commands.size(); ++i)
    {
        try
        {
            MushcoreApp::Instance().Process(m_commands[i]);
        }
        catch (CommandFail& e)
        {
            cerr << "*** Command failed: " << e.what() << endl;
        }
        catch (ExpressionFail& e)
        {
            cerr << "*** Command failed: " << e.what() << endl;
        }
        catch (FileFail& e)
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
MushcoreFunction::Print(ostream& inOut) const
{
    for (U32 i=0; i<m_commands.size(); ++i)
    {
        inOut << m_commands[i] << endl;
    }
}
