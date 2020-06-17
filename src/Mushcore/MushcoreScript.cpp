//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreScript.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } s/SG5rJzGwVP3+3Mk2AHsg
/*
 * $Id: MushcoreScript.cpp,v 1.9 2006/06/01 15:39:47 southa Exp $
 * $Log: MushcoreScript.cpp,v $
 * Revision 1.9  2006/06/01 15:39:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:16  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:13  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:16  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.3  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
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

MushcoreScript::MushcoreScript(std::istream& inIn)
{
    ReadFromStream(inIn);
}

MushcoreScript::MushcoreScript(const string& inContent)
{
    istringstream contentStream(inContent);
    ReadFromStream(contentStream);
}

void
MushcoreScript::ReadFromStream(istream& inIn)
{
    pair<tFunctionMapIterator, bool> p = m_functions.insert(pair<string, MushcoreFunction>("_global", MushcoreFunction("_global")));
    if (!p.second)
    {
        throw(MushcoreSyntaxFail("Duplicated function name _global"));
    }
    while (!inIn.eof())
    {
        string line;
        if (!inIn.good()) throw "Stream went bad";
        getline(inIn, line);
        p.first->second.CommandAdd(line);
    }
}


const MushcoreFunction&
MushcoreScript::FunctionGet(const string& inName) const
{
    tFunctionMapConstIterator p = m_functions.find(inName);

    if (p == m_functions.end())
    {
        throw(MushcoreRequestFail("Request for unknown function '"+inName+"'"));
    }
    return p->second;
}

void
MushcoreScript::Execute(void) const
{
    tFunctionMapConstIterator p = m_functions.find("_global");
    if (p != m_functions.end())
    {
        p->second.CoalesceErrorsExecute();
    }
}

void
MushcoreScript::Print(ostream& ioOut) const
{
    tFunctionMapConstIterator endValue = m_functions.end();
    
    for (tFunctionMapConstIterator p = m_functions.begin(); p != endValue; ++p)
    {
        if (p->second.NameGet() == "_global")
        {
            ioOut << p->second;
        }
        else
        {
            ioOut << "function " << p->second.NameGet() << endl;
            ioOut << "{" << endl << p->second << "}" << endl;
        }
    }
}
