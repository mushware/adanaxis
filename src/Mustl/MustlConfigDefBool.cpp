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
 * $Id: MustlConfigDefBool.cpp,v 1.4 2003/01/20 10:45:29 southa Exp $
 * $Log: MustlConfigDefBool.cpp,v $
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
    m_value = inValue.U32Get();
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
    MushcoreData<MustlConfigDef>::Sgl().Give(name, new MustlConfigDefBool(defaultValue));
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
