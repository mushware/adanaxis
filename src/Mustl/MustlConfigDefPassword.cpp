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

#include "MustlConfigDefPassword.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

MushcoreInstaller MustlConfigDefPassword(MustlConfigDefPassword::Install);

MustlConfigDefPassword::MustlConfigDefPassword(const string& inValue) :
MustlConfigDefString(inValue)
{
}

MustlConfigDefPassword::~MustlConfigDefPassword()
{
}

bool
MustlConfigDefPassword::FromPostRetrieve(const string& inName, const string& inData)
{
    bool found=false;
    MushcoreRegExp re("&"+inName+"=([^&$]*)");
    vector<string> matches;
    if (re.Search(inData, matches))
    {
        MUSHCOREASSERT(matches.size() == 1);
        string newValue=MustlUtils::RemoveMeta(matches[0]);
        if (newValue != "******")
        {
            ValueSet(MushcoreScalar(MustlUtils::RemoveMeta(newValue)));
            found=true;
        }
    }
    return found;
}

void
MustlConfigDefPassword::WebInputPrint(ostream& ioOut, const string& inName)
{
    ioOut << "<input name=\"" << MustlUtils::MakeWebSafe(inName) << "\" type=\"password\" size=\"20\" value=\"";
    if (ValueGet().StringGet() != 0)
    {
        ioOut << "******";
    }
    ioOut << "\">" << endl;
}

MushcoreScalar
MustlConfigDefPassword::MustlConfigPassword(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams != 2)
    {
        throw(MushcoreCommandFail("Usage: mustlconfigpassword(name, default value)"));
    }
    string name, defaultValue;
    ioCommand.PopParam(name);
    ioCommand.PopParam(defaultValue);
    MushcoreData<MustlConfigDef>::Instance().Give(name, new MustlConfigDefPassword(defaultValue));
    return MushcoreScalar(0);
}

void
MustlConfigDefPassword::Install(void)
{
MushcoreInterpreter::Instance().AddHandler("mustlconfigpassword", MustlConfigPassword);
}

