#ifndef COREFUNCTION_H
#define COREFUNCTION_H
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
 * $Id: CoreFunction.h,v 1.9 2002/10/22 20:41:58 southa Exp $
 * $Log: CoreFunction.h,v $
 * Revision 1.9  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.4  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.3  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.2  2002/05/24 16:23:10  southa
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

class CoreFunction
{
public:
    // CoreFunction() {}
    CoreFunction(const string& inStr): m_name(inStr) {}
    void AddCommand(const string& inStr) {if (inStr != "") m_commands.push_back(inStr);}
    const string& Name(void) const {return m_name;}
    const string& Command(Mushware::U32 inIndex) const {return m_commands[inIndex];}
    Mushware::U32 SizeGet(void) const {return m_commands.size();}
    const string& Line(Mushware::U32 inNum) const {return m_commands[inNum];}
    void Execute(void) const;
    void Print(std::ostream &inOut) const;
private:
    string m_name;
    std::vector<string> m_commands;
};

inline std::ostream& operator<<(std::ostream &inOut, const CoreFunction& inFunction)
{
    inFunction.Print(inOut);
    return inOut;
}

#endif
