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

#include "MustlConfigDefVal.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

MushcoreInstaller MustlConfigDefVak(MustlConfigDefVal::Install);

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
    vector<string> matches;
    if (re.Search(inData, matches))
    {
        MUSHCOREASSERT(matches.size() == 1);
        istringstream valueStream(matches[0]);
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
    MushcoreData<MustlConfigDef>::Instance().Give(name, new MustlConfigDefVal(defaultValue, lowLimit, highLimit));
    return MushcoreScalar(0);
}

void
MustlConfigDefVal::Install(void)
{
MushcoreInterpreter::Instance().AddHandler("mustlconfigfloat", MustlConfigFloat);
}
