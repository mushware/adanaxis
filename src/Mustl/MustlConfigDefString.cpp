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
 * $Id: MustlConfigDefString.cpp,v 1.3 2003/01/15 13:27:32 southa Exp $
 * $Log: MustlConfigDefString.cpp,v $
 * Revision 1.3  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.2  2003/01/14 20:46:11  southa
 * Post data handling
 *
 * Revision 1.1  2003/01/14 12:40:11  southa
 * Moved ConfigDefs into Mustl
 *
 */

#include "MustlConfigDefString.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

MushcoreInstaller MustlConfigDefStringInstaller(MustlConfigDefString::Install);

MustlConfigDefString::MustlConfigDefString(const string& inValue) :
m_value(inValue)
{
}

MustlConfigDefString::~MustlConfigDefString()
{
}

const MushcoreScalar
MustlConfigDefString::ValueGet(void) const
{
    return MushcoreScalar(m_value);
}

void
MustlConfigDefString::ValueSet(const MushcoreScalar& inValue)
{
    m_value = inValue.StringGet();
}

bool
MustlConfigDefString::FromPostRetrieve(const string& inName, const string& inData)
{
    bool found=false;
    MushcoreRegExp re("&"+inName+"=([^&$]*)");
    vector<string> matches;
    if (re.Search(inData, matches))
    {
        MUSHCOREASSERT(matches.size() == 1);
        m_value=MustlUtils::RemoveMeta(matches[0]);
        found=true;
    }
    return found;
}

void
MustlConfigDefString::WebInputPrint(ostream& ioOut, const string& inName)
{
    ioOut << "<input name=\"" << MustlUtils::MakeWebSafe(inName) << "\" type=\"text\" size=\"20\" value=\"" << MustlUtils::MakeWebSafe(m_value) << "\">" << endl;
}

MushcoreScalar
MustlConfigDefString::MustlConfigString(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams != 2)
    {
        throw(MushcoreCommandFail("Usage: mustlconfigstring(name, default value)"));
    }
    string name, defaultValue;
    ioCommand.PopParam(name);
    ioCommand.PopParam(defaultValue);
    MushcoreData<MustlConfigDef>::Sgl().Give(name, new MustlConfigDefString(defaultValue));
    return MushcoreScalar(0);
}

void
MustlConfigDefString::Install(void)
{
MushcoreInterpreter::Sgl().AddHandler("mustlconfigstring", MustlConfigString);
}

void
MustlConfigDefString::NullFunction(void)
{
}

