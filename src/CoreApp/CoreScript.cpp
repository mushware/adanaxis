/*
 * $Id: CoreScript.cpp,v 1.2 2002/05/10 16:39:37 southa Exp $
 * $Log: CoreScript.cpp,v $
 * Revision 1.2  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/03/01 12:21:25  southa
 * Added first CoreScript code
 *
 */

#include "CoreScript.h"
#include "CoreException.h"

CoreScript::CoreScript(const string& inFilename)
{
    ifstream inFile(inFilename.c_str());
    if (!inFile)
    {
        throw (FileFail(inFilename, "Failed to open"));
    }
    ReadFromStream(inFile);
}

void
CoreScript::ReadFromStream(istream& inIn)
{
    m_functions.push_back(CoreFunction("_global"));
    while (!inIn.eof())
    {
        string line;
        if (!inIn.good()) throw "Stream went bad";
        getline(inIn, line);
        m_functions.back().AddCommand(line);
    }
}

void
CoreScript::ostreamPrint(ostream& inOut) const
{
    for (tSize i=0; i<m_functions.size(); ++i)
    {
        const CoreFunction& func=m_functions[i];
        inOut << "Function " << func.Name() << ":" << endl;
        for (tSize j=0; j<func.SizeGet(); ++j)
        {
            inOut << func.Command(j) << endl;
        }
        inOut << endl;
    }
}
