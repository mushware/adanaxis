#ifndef CORESCRIPT_HP
#define CORESCRIPT_HP
/*
 * $Id: CoreScript.h,v 1.1 2002/05/10 16:39:38 southa Exp $
 * $Log: CoreScript.h,v $
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
    CoreScript(const string& inFilename);
    CoreScript(istream& inIn) {ReadFromStream(inIn);}
    void ostreamPrint(ostream& inOut) const;
    tSize SizeGet(void) const {return m_functions[0].SizeGet();}
    const string& Line(tSize inNum) const {return m_functions[0].Line(inNum);}
    
private:
    void ReadFromStream(istream& inIn);
    vector<CoreFunction> m_functions;
};

inline ostream& operator<<(ostream &inOut, const CoreScript& inCoreScript)
{
    inCoreScript.ostreamPrint(inOut);
    return inOut;
}
#endif
