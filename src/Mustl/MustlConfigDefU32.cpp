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
 * $Id: MustlConfigDefU32.cpp,v 1.5 2003/01/20 12:23:24 southa Exp $
 * $Log: MustlConfigDefU32.cpp,v $
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

#include "MustlConfigDefU32.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

MushcoreInstaller MustlConfigDefU32Installer(MustlConfigDefU32::Install);

MustlConfigDefU32::MustlConfigDefU32(U32 inValue, U32 inLowLimit, U32 inHighLimit) :
    m_value(inValue),
    m_lowLimit(inLowLimit),
    m_highLimit(inHighLimit)
{
}

MustlConfigDefU32::~MustlConfigDefU32()
{
}

const MushcoreScalar
MustlConfigDefU32::ValueGet(void) const
{
    return MushcoreScalar(m_value);
}

void
MustlConfigDefU32::ValueSet(const MushcoreScalar& inValue)
{
    U32 value=inValue.U32Get();
    if (value < m_lowLimit || value >= m_highLimit)
    {
        ostringstream message;
        message << "Value out of range (" << m_lowLimit << " < " << inValue << " < " << m_highLimit << ")";
        throw(MushcoreDataFail(message.str()));
    }
    m_value=value;
}

bool
MustlConfigDefU32::FromPostRetrieve(const string& inName, const string& inData)
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
MustlConfigDefU32::WebInputPrint(ostream& ioOut, const string& inName)
{
    ioOut << "<input name=\"" << MustlUtils::MakeWebSafe(inName) << "\" type=\"text\" size=\"6\" value=\"" << MustlUtils::MakeWebSafe(m_value) << "\">" << endl;
}

MushcoreScalar
MustlConfigDefU32::MustlConfigUnsigned(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams != 4)
    {
        throw(MushcoreCommandFail("Usage: mustlconfigunsigned(name, default value, low limit, high limit)"));
    }
    string name;
    U32 defaultValue, lowLimit, highLimit;
    ioCommand.PopParam(name);
    ioCommand.PopParam(defaultValue);
    ioCommand.PopParam(lowLimit);
    ioCommand.PopParam(highLimit);
    MushcoreData<MustlConfigDef>::Sgl().Give(name, new MustlConfigDefU32(defaultValue, lowLimit, highLimit));
    return MushcoreScalar(0);
}

void
MustlConfigDefU32::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("mustlconfigunsigned", MustlConfigUnsigned);
}

void
MustlConfigDefU32::NullFunction(void)
{
}
