//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefBool.cpp
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } sq5csRW++79EHkcLhi+knA
/*
 * $Id: MustlConfigDefBool.cpp,v 1.7 2003/08/21 23:09:22 southa Exp $
 * $Log: MustlConfigDefBool.cpp,v $
 * Revision 1.7  2003/08/21 23:09:22  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/02/04 14:54:51  southa
 * Build fixes
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

#include "MustlConfigDefBool.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

MushcoreInstaller MustlConfigDefBoolInstaller(MustlConfigDefBool::Install);

MustlConfigDefBool::MustlConfigDefBool(bool inValue) :
m_value(inValue)
{
}

MustlConfigDefBool::~MustlConfigDefBool()
{
}

const MushcoreScalar
MustlConfigDefBool::ValueGet(void) const
{
    return MushcoreScalar(m_value);
}

void
MustlConfigDefBool::ValueSet(const MushcoreScalar& inValue)
{
    m_value = !(!inValue.U32Get());
}

bool
MustlConfigDefBool::FromPostRetrieve(const string& inName, const string& inData)
{
    bool found=false;
    MushcoreRegExp re("&"+inName+"=([^&$]+)");
    MushcoreRegExp::tMatches regExpMatches;
    if (re.Search(regExpMatches, inData))
    {
        MUSHCOREASSERT(regExpMatches.size() == 1);
        istringstream valueStream(MustlUtils::RemoveMeta(regExpMatches[0]));
        U32 value;
        if (valueStream >> value)
        {
            ValueSet(MushcoreScalar(value));
            found=true;
        }
    }
    return found;
}

void
MustlConfigDefBool::WebInputPrint(ostream& ioOut, const string& inName)
{
    ioOut << "<input name=\"" << MustlUtils::MakeWebSafe(inName) << "\" type=\"checkbox\" ";
    if (m_value) ioOut << "checked ";
    ioOut << "value=\"1\">" << endl;
    // If the checkbox is unchecked there will be no value output, so this
    // hidden value makes sure that a zero-valued result is generated
    ioOut << "<input name =\"" << MustlUtils::MakeWebSafe(inName) << "\" type=\"hidden\" value=\"0\"" << endl;
}

MushcoreScalar
MustlConfigDefBool::MustlConfigBool(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams != 2)
    {
        throw(MushcoreCommandFail("Usage: mustlconfigbool(name, default value)"));
    }
    string name;
    U32 defaultValue;
    ioCommand.PopParam(name);
    ioCommand.PopParam(defaultValue);
    MushcoreData<MustlConfigDef>::Sgl().Give(name, new MustlConfigDefBool(!(!defaultValue)));
    return MushcoreScalar(0);
}

void
MustlConfigDefBool::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("mustlconfigbool", MustlConfigBool);
}

void
MustlConfigDefBool::NullFunction(void)
{
}
