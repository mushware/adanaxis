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
 * $Id: MustlConfigDefMenuString.cpp,v 1.2 2003/01/14 20:46:11 southa Exp $
 * $Log: MustlConfigDefMenuString.cpp,v $
 * Revision 1.2  2003/01/14 20:46:11  southa
 * Post data handling
 *
 * Revision 1.1  2003/01/14 12:40:10  southa
 * Moved ConfigDefs into Mustl
 *
 */

#include "MustlConfigDefMenuString.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

MushcoreInstaller MustlConfigDefMenuStringInstaller(MustlConfigDefMenuString::Install);

MustlConfigDefMenuString::MustlConfigDefMenuString(const string& inValue, const string& inMenu) :
MustlConfigDefString(inValue),
m_menu(inMenu)
{
}

MustlConfigDefMenuString::~MustlConfigDefMenuString()
{
}

void
MustlConfigDefMenuString::WebInputPrint(ostream& ioOut, const string& inName)
{
    SelectPrologue(ioOut, inName);
    U32 endPos=m_menu.size()-1;
    U32 currentPos=0;
    string currentValue = ValueGet().StringGet();

    while (currentPos < endPos)
    {
        U32 equalsPos=m_menu.find('=', currentPos);
        if (equalsPos == m_menu.npos) break;
        U32 ampPos=m_menu.find('&', equalsPos);
        if (ampPos == m_menu.npos) ampPos = endPos+1; // Where the ampersand would be

        SelectOption(ioOut,
                     m_menu.substr(equalsPos+1, ampPos - (equalsPos+1)),
                     m_menu.substr(currentPos, equalsPos - currentPos),
                     (m_menu.substr(currentPos, equalsPos - currentPos) == currentValue));
        currentPos = ampPos+1;
    }
    SelectEpilogue(ioOut);
}

MushcoreScalar
MustlConfigDefMenuString::MustlConfigMenuString(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams != 3)
    {
        throw(MushcoreCommandFail("Usage: mustlconfigmenustring(name, default value, menu string)"));
    }
    string name, defaultValue, menuStr;
    ioCommand.PopParam(name);
    ioCommand.PopParam(defaultValue);
    ioCommand.PopParam(menuStr);
    MushcoreData<MustlConfigDef>::Instance().Give(name, new MustlConfigDefMenuString(defaultValue, menuStr));
    return MushcoreScalar(0);
}

void
MustlConfigDefMenuString::Install(void)
{
    MushcoreInterpreter::Instance().AddHandler("mustlconfigmenustring", MustlConfigMenuString);
}

void
MustlConfigDefMenuString::NullFunction(void)
{
}
