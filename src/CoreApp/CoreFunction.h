#ifndef COREFUNCTION_H
#define COREFUNCTION_H
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
 * $Id: CoreFunction.h,v 1.4 2002/05/29 08:56:16 southa Exp $
 * $Log: CoreFunction.h,v $
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
    const string& Command(tSize inIndex) const {return m_commands[inIndex];}
    tSize SizeGet(void) const {return m_commands.size();}
    const string& Line(tSize inNum) const {return m_commands[inNum];}
    void Execute(void) const;
    void Print(ostream &inOut) const;
private:
    string m_name;
    vector<string> m_commands;
};

inline ostream& operator<<(ostream &inOut, const CoreFunction& inFunction)
{
    inFunction.Print(inOut);
    return inOut;
}

#endif
