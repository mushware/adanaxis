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
 * $Id: CoreScript.cpp,v 1.6 2002/06/27 12:36:04 southa Exp $
 * $Log: CoreScript.cpp,v $
 * Revision 1.6  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.5  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.4  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.3  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 * Revision 1.2  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/03/01 12:21:25  southa
 * Added first CoreScript code
 *
 */

#include "CoreScript.h"
#include "CoreException.h"

CoreScript::CoreScript()
{
}

CoreScript::CoreScript(const string& inContent)
{
    istringstream strm(inContent);
    ReadFromStream(strm);
}

void
CoreScript::ReadFromStream(istream& inIn)
{
    pair<map<string, CoreFunction>::iterator, bool> p =
        m_functions.insert(pair<string, CoreFunction>("_global", CoreFunction("_global")));
    if (!p.second)
    {
        throw(LogicFail("Duplicated function name _global"));
    }
    while (!inIn.eof())
    {
        string line;
        if (!inIn.good()) throw "Stream went bad";
        getline(inIn, line);
        p.first->second.AddCommand(line);
    }
}


const CoreFunction&
CoreScript::FunctionGet(const string& inName) const
{
    map<string, CoreFunction>::const_iterator p = m_functions.find(inName);

    if (p == m_functions.end())
    {
        throw(LogicFail("Request for unknown function '"+inName+"'"));
    }
    return p->second;
}

void
CoreScript::Execute(void) const
{
    map<string, CoreFunction>::const_iterator p = m_functions.find("_global");
    if (p == m_functions.end())
    {
        cerr << "Warning: Execution of script with no contents" << endl;
        return;
    }
    p->second.Execute();
}

void
CoreScript::ostreamPrint(ostream& inOut) const
{
    for (map<string, CoreFunction>::const_iterator p = m_functions.begin();
         p != m_functions.end(); ++p)
    {
        if (p->second.Name() == "_global")
        {
            inOut << p->second;
        }
        else
        {
            inOut << "function " << p->second.Name() << endl;
            inOut << "{" << endl << p->second << "}" << endl;
        }
    }
}
