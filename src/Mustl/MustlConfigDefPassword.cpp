/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MustlConfigDefPassword.cpp,v 1.6 2003/01/20 12:23:24 southa Exp $
 * $Log: MustlConfigDefPassword.cpp,v $
 * Revision 1.6  2003/01/20 12:23:24  southa
 * Code and interface tidying
 *
 * Revision 1.5  2003/01/20 10:45:30  southa
 * Singleton tidying
 *
 * Revision 1.4  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
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

#include "MustlConfigDefPassword.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

MushcoreInstaller MustlConfigDefPasswordInstaller(MustlConfigDefPassword::Install);

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
    MushcoreRegExp::tMatches regExpMatches;
    if (re.Search(regExpMatches, inData))
    {
        MUSHCOREASSERT(regExpMatches.size() == 1);
        string newValue=MustlUtils::RemoveMeta(regExpMatches[0]);
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
    if (ValueGet().StringGet() != "")
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
    MushcoreData<MustlConfigDef>::Sgl().Give(name, new MustlConfigDefPassword(defaultValue));
    return MushcoreScalar(0);
}

void
MustlConfigDefPassword::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("mustlconfigpassword", MustlConfigPassword);
}

void
MustlConfigDefPassword::NullFunction(void)
{
}

