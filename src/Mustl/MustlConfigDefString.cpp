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
 * $Id$
 * $Log$
 */

#include "MustlConfigDefString.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

MushcoreInstaller MustlConfigDefString(MustlConfigDefString::Install);

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
    MushcoreData<MustlConfigDef>::Instance().Give(name, new MustlConfigDefString(defaultValue));
    return MushcoreScalar(0);
}

void
MustlConfigDefString::Install(void)
{
MushcoreInterpreter::Instance().AddHandler("mustlconfigstring", MustlConfigString);
}

