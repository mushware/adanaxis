//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefString.cpp
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } k/+BIASy4+LsyYxOdsW//A
/*
 * $Id: MustlConfigDefString.cpp,v 1.10 2006/06/01 15:39:51 southa Exp $
 * $Log: MustlConfigDefString.cpp,v $
 * Revision 1.10  2006/06/01 15:39:51  southa
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
 * Revision 1.6  2003/08/21 23:09:23  southa
 * Fixed file headers
 *
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

