/*
 * $Id: CoreFunction.cpp,v 1.1 2002/05/28 22:36:44 southa Exp $
 * $Log: CoreFunction.cpp,v $
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
