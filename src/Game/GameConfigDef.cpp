/*
 * $Id$
 * $Log$
 */

#include "GameConfigDef.h"

auto_ptr< CoreData<GameConfigDef> > CoreData<GameConfigDef>::m_instance;

GameConfigDef::~GameConfigDef()
{
}

GameConfigDefU32::GameConfigDefU32(U32 inValue, U32 inLowLimit, U32 inHighLimit) :
    m_value(inValue),
    m_lowLimit(inLowLimit),
    m_highLimit(inHighLimit)
{
}

GameConfigDefU32::~GameConfigDefU32()
{
}

const CoreScalar
GameConfigDefU32::ValueGet(void) const
{
    return CoreScalar(m_value);
}

void
GameConfigDefU32::ValueSet(const CoreScalar& inValue)
{
    U32 value=inValue.U32Get();
    if (value < m_lowLimit || value >= m_highLimit)
    {
        ostringstream message;
        message << "Value out of range (" << m_lowLimit << " < " << inValue << " < " << m_highLimit << ")";
        throw(ValueFail(message.str()));
    }
    m_value=value;
}

bool
GameConfigDefU32::FromPostRetrieve(const string& inName, const string& inData)
{
    bool found=false;
    CoreRegExp re("&"+inName+"=([^&$]+)");
    vector<string> matches;
    if (re.Search(inData, matches))
    {
        COREASSERT(matches.size() == 1);
        istringstream valueStream(matches[0]);
        U32 value;
        if (valueStream >> value)
        {
            if (value < m_lowLimit || value >= m_highLimit)
            {
                ostringstream message;
                message << "Value for " << inName <<" out of range (" << m_lowLimit << " < " << value << " < " << m_highLimit << ")";
                throw(CommandFail(message.str()));
            }
            m_value=value;
            found=true;
        }
    }
    return found;
}

// -----

GameConfigDefString::GameConfigDefString(const string& inValue) :
    m_value(inValue)
{
}

GameConfigDefString::~GameConfigDefString()
{
}

const CoreScalar
GameConfigDefString::ValueGet(void) const
{
    return CoreScalar(m_value);
}

void
GameConfigDefString::ValueSet(const CoreScalar& inValue)
{
    m_value = inValue.StringGet();
}

bool
GameConfigDefString::FromPostRetrieve(const string& inName, const string& inData)
{
    bool found=false;
    CoreRegExp re("&"+inName+"=([^&$]+)");
    vector<string> matches;
    if (re.Search(inData, matches))
    {
        COREASSERT(matches.size() == 1);
        m_value=matches[0];
        found=true;
    }
    return found;
}
