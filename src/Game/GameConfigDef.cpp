/*
 * $Id: GameConfigDef.cpp,v 1.1 2002/11/14 17:29:08 southa Exp $
 * $Log: GameConfigDef.cpp,v $
 * Revision 1.1  2002/11/14 17:29:08  southa
 * Config database
 *
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

void
GameConfigDefU32::WebInputPrint(ostream& ioOut, const string& inName)
{
    ioOut << "<input name=\"" << inName << "\" type=\"text\" size=\"6\" value=\"" << m_value << "\">" << endl;
}

// -----

GameConfigDefString::GameConfigDefString(const string& inValue, const string& inMenu="") :
    m_value(inValue),
    m_menu(inMenu)
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
    CoreRegExp re("&"+inName+"=([^&$]*)");
    vector<string> matches;
    if (re.Search(inData, matches))
    {
        COREASSERT(matches.size() == 1);
        m_value=matches[0];
        found=true;
    }
    return found;
}

void
GameConfigDefString::WebInputPrint(ostream& ioOut, const string& inName)
{

    if (m_menu.size() == 0)
    {
        ioOut << "<input name=\"" << inName << "\" type=\"text\" size=\"20\" value=\"" << m_value << "\">" << endl;
    }
    else
    {
        SelectPrologue(ioOut, inName);
        U32 endPos=m_menu.size()-1;
        U32 currentPos=0;
        while (currentPos < endPos)
        {
            U32 equalsPos=m_menu.find('=', currentPos);
            if (equalsPos == m_menu.npos) break;
            U32 ampPos=m_menu.find('&', equalsPos);
            if (ampPos == m_menu.npos) ampPos = endPos+1; // Where the ampersand would be
            
            SelectOption(ioOut,
                         m_menu.substr(equalsPos+1, ampPos - (equalsPos+1)),
                         m_menu.substr(currentPos, equalsPos - currentPos),
                        (m_menu.substr(currentPos, equalsPos - currentPos) == m_value));
            currentPos = ampPos+1;
        }
    
        SelectEpilogue(ioOut);
    }
}

void
GameConfigDef::SelectPrologue(ostream& ioOut, const string& inName)
{
    ioOut << "<select name=\"" << inName << "\">" << endl;
}

void
GameConfigDef::SelectOption(ostream& ioOut, const string& inName, const string& inValue, bool inSelected)
{
    ioOut << "<option ";
    if (inSelected) ioOut << "selected ";
    ioOut << "value=\"" << inValue << "\">";
    ioOut << inName;
    ioOut << "</option>" << endl;
}

void
GameConfigDef::SelectOption(ostream& ioOut, const string& inName, U32 inValue, bool inSelected)
{
    ostringstream value;
    value << inValue;
    SelectOption(ioOut, inName, value.str(), inSelected);
}

void
GameConfigDef::SelectEpilogue(ostream& ioOut)
{
    ioOut << "</select>" << endl;
}


