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
 * $Id: MushcoreScript.cpp,v 1.2 2003/01/12 17:33:00 southa Exp $
 * $Log: MushcoreScript.cpp,v $
 * Revision 1.2  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.12  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.11  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.10  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.7  2002/07/06 18:04:16  southa
 * More designer work
 *
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
 * Added first MushcoreScript code
 *
 */

#include "MushcoreScript.h"
#include "MushcoreFail.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MushcoreScript::MushcoreScript()
{
}

MushcoreScript::MushcoreScript(const string& inContent)
{
    istringstream strm(inContent);
    ReadFromStream(strm);
}

void
MushcoreScript::ReadFromStream(istream& inIn)
{
    pair<map<string, MushcoreFunction>::iterator, bool> p =
        m_functions.insert(pair<string, MushcoreFunction>("_global", MushcoreFunction("_global")));
    if (!p.second)
    {
        throw(MushcoreLogicFail("Duplicated function name _global"));
    }
    while (!inIn.eof())
    {
        string line;
        if (!inIn.good()) throw "Stream went bad";
        getline(inIn, line);
        p.first->second.AddCommand(line);
    }
}


const MushcoreFunction&
MushcoreScript::FunctionGet(const string& inName) const
{
    map<string, MushcoreFunction>::const_iterator p = m_functions.find(inName);

    if (p == m_functions.end())
    {
        throw(MushcoreLogicFail("Request for unknown function '"+inName+"'"));
    }
    return p->second;
}

void
MushcoreScript::Execute(void) const
{
    map<string, MushcoreFunction>::const_iterator p = m_functions.find("_global");
    if (p != m_functions.end())
    {
        p->second.CoalesceErrorsExecute();
    }
}

void
MushcoreScript::ostreamPrint(ostream& inOut) const
{
    for (map<string, MushcoreFunction>::const_iterator p = m_functions.begin();
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
