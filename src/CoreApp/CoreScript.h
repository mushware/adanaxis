#ifndef CORESCRIPT_HP
#define CORESCRIPT_HP
/*
 * $Id: CoreScript.h,v 1.2 2002/05/24 16:23:08 southa Exp $
 * $Log: CoreScript.h,v $
 * Revision 1.2  2002/05/24 16:23:08  southa
 * Config and typenames
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/03/08 22:48:14  southa
 * Added first avarisse code
 *
 * Revision 1.2  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.1  2002/03/01 12:21:25  southa
 * Added first CoreScript code
 *
 */

#include "CoreStandard.h"
#include "CoreFunction.h"

class CoreScript
{
public:
    CoreScript();
    CoreScript(const string& inContent);
    CoreScript(istream& inIn) {ReadFromStream(inIn);}
    void ostreamPrint(ostream& inOut) const;
    const CoreFunction& FunctionGet(const string& inName) const;
    void Execute(void) const;
    
private:
    void ReadFromStream(istream& inIn);
    map<string, CoreFunction> m_functions;
};

inline ostream& operator<<(ostream &inOut, const CoreScript& inCoreScript)
{
    inCoreScript.ostreamPrint(inOut);
    return inOut;
}
#endif
