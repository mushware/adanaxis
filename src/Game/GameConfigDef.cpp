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
 * $Id: GameConfigDef.cpp,v 1.7 2002/12/20 13:17:38 southa Exp $
 * $Log: GameConfigDef.cpp,v $
 * Revision 1.7  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.5  2002/11/25 18:02:56  southa
 * Mushware ID work
 *
 * Revision 1.4  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.3  2002/11/15 11:47:55  southa
 * Web processing and error handling
 *
 * Revision 1.2  2002/11/14 19:35:30  southa
 * Configuration work
 *
 * Revision 1.1  2002/11/14 17:29:08  southa
 * Config database
 *
 */

#include "GameConfigDef.h"

#include "mushMedia.h"

using namespace Mushware;
using namespace std;

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
            ValueSet(CoreScalar(value));
            found=true;
        }
    }
    return found;
}

void
GameConfigDefU32::WebInputPrint(ostream& ioOut, const string& inName)
{
    ioOut << "<input name=\"" << MustlUtils::MakeWebSafe(inName) << "\" type=\"text\" size=\"6\" value=\"" << MustlUtils::MakeWebSafe(m_value) << "\">" << endl;
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
        m_value=MustlUtils::RemoveMeta(matches[0]);
        found=true;
    }
    return found;
}

void
GameConfigDefString::WebInputPrint(ostream& ioOut, const string& inName)
{

    if (m_menu.size() == 0)
    {
        ioOut << "<input name=\"" << MustlUtils::MakeWebSafe(inName) << "\" type=\"text\" size=\"20\" value=\"" << MustlUtils::MakeWebSafe(m_value) << "\">" << endl;
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

// -----

GameConfigDefPassword::GameConfigDefPassword(const string& inValue) :
    m_value(inValue)
{
}

GameConfigDefPassword::~GameConfigDefPassword()
{
}

const CoreScalar
GameConfigDefPassword::ValueGet(void) const
{
    return CoreScalar(m_value);
}

void
GameConfigDefPassword::ValueSet(const CoreScalar& inValue)
{
    m_value = inValue.StringGet();
}

bool
GameConfigDefPassword::FromPostRetrieve(const string& inName, const string& inData)
{
    bool found=false;
    CoreRegExp re("&"+inName+"=([^&$]*)");
    vector<string> matches;
    if (re.Search(inData, matches))
    {
        COREASSERT(matches.size() == 1);
        string newValue=MustlUtils::RemoveMeta(matches[0]);
        if (newValue != "******")
        {
            m_value=MustlUtils::RemoveMeta(newValue);
            found=true;
        }
    }
    return found;
}

void
GameConfigDefPassword::WebInputPrint(ostream& ioOut, const string& inName)
{
    ioOut << "<input name=\"" << MustlUtils::MakeWebSafe(inName) << "\" type=\"password\" size=\"20\" value=\"";
    if (m_value.size() != 0)
    {
        ioOut << "******";
    }
    ioOut << "\">" << endl;
}

// -----

GameConfigDefBool::GameConfigDefBool(bool inValue) :
m_value(inValue)
{
}

GameConfigDefBool::~GameConfigDefBool()
{
}

const CoreScalar
GameConfigDefBool::ValueGet(void) const
{
    return CoreScalar(m_value);
}

void
GameConfigDefBool::ValueSet(const CoreScalar& inValue)
{
    m_value = inValue.U32Get();
}

bool
GameConfigDefBool::FromPostRetrieve(const string& inName, const string& inData)
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
            ValueSet(CoreScalar(value));
            found=true;
        }
    }
    return found;    
}

void
GameConfigDefBool::WebInputPrint(ostream& ioOut, const string& inName)
{
    ioOut << "<input name=\"" << MustlUtils::MakeWebSafe(inName) << "\" type=\"checkbox\" ";
    if (m_value) ioOut << "checked ";
    ioOut << "value=\"1\">" << endl;
    ioOut << "<input name =\"" << MustlUtils::MakeWebSafe(inName) << "\" type=\"hidden\" value=\"0\"" << endl;
}

// -----

void
GameConfigDef::SelectPrologue(ostream& ioOut, const string& inName)
{
    ioOut << "<select name=\"" << MustlUtils::MakeWebSafe(inName) << "\">" << endl;
}

void
GameConfigDef::SelectOption(ostream& ioOut, const string& inName, const string& inValue, bool inSelected)
{
    ioOut << "<option ";
    if (inSelected) ioOut << "selected ";
    ioOut << "value=\"" << MustlUtils::MakeWebSafe(inValue) << "\">";
    ioOut << MustlUtils::MakeWebSafe(inName);
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


