/*
 * $Id$
 * $Log$
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
