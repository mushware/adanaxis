/*
 * $Id: CoreEnv.cpp,v 1.1 2002/03/07 22:24:33 southa Exp $
 * $Log: CoreEnv.cpp,v $
 * Revision 1.1  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 */

#include "CoreEnv.hp"
#include "CoreApp.hp"

void
CoreEnv::Enter(const CoreScript& inScript)
{
    cerr << "Entered script" << endl << inScript << endl;
    for (Size i=0; i<inScript.SizeGet(); ++i)
    {
        CoreApp::Instance().Process(inScript.Line(i));
    }
}
