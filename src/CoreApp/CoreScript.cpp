/*
 * $Id$
 * $Log$
 */

#include "CoreScript.hp"
#include "CoreException.hp"

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
    for (Size i=0; i<m_functions.size(); ++i)
    {
        const CoreFunction& func=m_functions[i];
        inOut << "Function " << func.Name() << ":" << endl;
        for (Size j=0; j<func.SizeGet(); ++j)
        {
            inOut << func.Command(j) << endl;
        }
        inOut << endl;
    }
}
