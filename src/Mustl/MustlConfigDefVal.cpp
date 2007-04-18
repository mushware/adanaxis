//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefVal.cpp
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
//%Header } UV/HjVtq4eYWv57AmozDOA
/*
 * $Id: MustlConfigDefVal.cpp,v 1.10 2006/06/01 15:39:51 southa Exp $
 * $Log: MustlConfigDefVal.cpp,v $
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
 * Revision 1.6  2003/08/21 23:09:24  southa
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

#include "MustlConfigDefVal.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

MushcoreInstaller MustlConfigDefValInstaller(MustlConfigDefVal::Install);

MustlConfigDefVal::MustlConfigDefVal(tVal inValue, tVal inLowLimit, tVal inHighLimit) :
m_value(inValue),
m_lowLimit(inLowLimit),
m_highLimit(inHighLimit)
{
}

MustlConfigDefVal::~MustlConfigDefVal()
{
}

const MushcoreScalar
MustlConfigDefVal::ValueGet(void) const
{
    return MushcoreScalar(m_value);
}

void
MustlConfigDefVal::ValueSet(const MushcoreScalar& inValue)
{
    tVal value=inValue.ValGet();
    if (value < m_lowLimit || value >= m_highLimit)
    {
        ostringstream message;
        message << "Value out of range (" << m_lowLimit << " < " << inValue << " < " << m_highLimit << ")";
        throw(MushcoreDataFail(message.str()));
    }
    m_value=value;
}

bool
MustlConfigDefVal::FromPostRetrieve(const string& inName, const string& inData)
{
    bool found=false;
    MushcoreRegExp re("&"+inName+"=([^&$]+)");
    MushcoreRegExp::tMatches regExpMatches;
    if (re.Search(regExpMatches, inData))
    {
        MUSHCOREASSERT(regExpMatches.size() == 1);
        istringstream valueStream(MustlUtils::RemoveMeta(regExpMatches[0]));
        tVal value;
        if (valueStream >> value)
        {
            ValueSet(MushcoreScalar(value));
            found=true;
        }
    }
    return found;
}

void
MustlConfigDefVal::WebInputPrint(ostream& ioOut, const string& inName)
{
    ioOut << "<input name=\"" << MustlUtils::MakeWebSafe(inName) << "\" type=\"text\" size=\"6\" value=\"" << MustlUtils::MakeWebSafe(m_value) << "\">" << endl;
}

MushcoreScalar
MustlConfigDefVal::MustlConfigFloat(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams != 4)
    {
        throw(MushcoreCommandFail("Usage: mustlconfigfloat(name, default value, low limit, high limit)"));
    }
    string name;
    U32 defaultValue, lowLimit, highLimit;
    ioCommand.PopParam(name);
    ioCommand.PopParam(defaultValue);
    ioCommand.PopParam(lowLimit);
    ioCommand.PopParam(highLimit);
    MushcoreData<MustlConfigDef>::Sgl().Give(name, new MustlConfigDefVal(defaultValue, lowLimit, highLimit));
    return MushcoreScalar(0);
}

void
MustlConfigDefVal::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("mustlconfigfloat", MustlConfigFloat);
}

void
MustlConfigDefVal::NullFunction(void)
{
}
