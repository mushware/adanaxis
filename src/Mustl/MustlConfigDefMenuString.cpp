//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefMenuString.cpp
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
//%Header } 8PBy4QQPl2SGSYzX3GimEg
/*
 * $Id: MustlConfigDefMenuString.cpp,v 1.10 2006/06/01 15:39:50 southa Exp $
 * $Log: MustlConfigDefMenuString.cpp,v $
 * Revision 1.10  2006/06/01 15:39:50  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:22  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/20 12:23:24  southa
 * Code and interface tidying
 *
 * Revision 1.4  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.3  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
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
    MushcoreData<MustlConfigDef>::Sgl().Give(name, new MustlConfigDefMenuString(defaultValue, menuStr));
    return MushcoreScalar(0);
}

void
MustlConfigDefMenuString::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("mustlconfigmenustring", MustlConfigMenuString);
}

void
MustlConfigDefMenuString::NullFunction(void)
{
}
