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
 * $Id: MustlConfigDefString.cpp,v 1.5 2003/01/20 12:23:24 southa Exp $
 * $Log: MustlConfigDefString.cpp,v $
 * Revision 1.5  2003/01/20 12:23:24  southa
 * Code and interface tidying
 *
 * Revision 1.4  2003/01/20 10:45:30  southa
 * Singleton tidying
 *
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
    MushcoreRegExp::tMatches regExpMatches;
    if (re.Search(regExpMatches, inData))
    {
        MUSHCOREASSERT(regExpMatches.size() == 1);
        m_value=MustlUtils::RemoveMeta(regExpMatches[0]);
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
MushcoreInterpreter::Sgl().HandlerAdd("mustlconfigstring", MustlConfigString);
}

void
MustlConfigDefString::NullFunction(void)
{
}

