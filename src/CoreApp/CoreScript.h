#ifndef CORESCRIPT_H
#define CORESCRIPT_H
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
 * $Id: CoreScript.h,v 1.8 2002/10/22 20:41:59 southa Exp $
 * $Log: CoreScript.h,v $
 * Revision 1.8  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.3  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
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

#include "CoreFunction.h"
#include "CoreStandard.h"

class CoreScript
{
public:
    CoreScript();
    CoreScript(const string& inContent);
    CoreScript(istream& inIn) {ReadFromStream(inIn);}
    void ostreamPrint(std::ostream& inOut) const;
    const CoreFunction& FunctionGet(const string& inName) const;
    void Execute(void) const;
    
private:
    void ReadFromStream(istream& inIn);
    std::map<string, CoreFunction> m_functions;
};

inline std::ostream& operator<<(std::ostream &inOut, const CoreScript& inCoreScript)
{
    inCoreScript.ostreamPrint(inOut);
    return inOut;
}
#endif
