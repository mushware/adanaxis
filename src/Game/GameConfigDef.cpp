//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameConfigDef.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } TwbWoOrPtUKoOEt+DCSp2g
/*
 * $Id: GameConfigDef.cpp,v 1.20 2004/09/27 22:42:08 southa Exp $
 * $Log: GameConfigDef.cpp,v $
 * Revision 1.20  2004/09/27 22:42:08  southa
 * MSVC compilation fixes
 *
 * Revision 1.19  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.18  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.17  2003/08/21 23:08:36  southa
 * Fixed file headers
 *
 * Revision 1.16  2003/02/05 17:06:35  southa
 * Build fixes
 *
 * Revision 1.15  2003/01/18 13:33:56  southa
 * Created MushcoreSingleton
 *
 * Revision 1.14  2003/01/17 13:30:38  southa
 * Source conditioning and build fixes
 *
 * Revision 1.13  2003/01/17 12:20:40  southa
 * Fixed auto_ptr duplication
 *
 * Revision 1.12  2003/01/13 14:31:56  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.11  2003/01/12 17:32:52  southa
 * Mushcore work
 *
 * Revision 1.10  2003/01/09 14:57:00  southa
 * Created Mushcore
 *
 * Revision 1.9  2003/01/07 17:13:41  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.8  2002/12/29 20:59:54  southa
 * More build fixes
 *
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
#include "GameSTL.h"

#include "mushMedia.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(GameConfigDef);

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

const MushcoreScalar
GameConfigDefU32::ValueGet(void) const
{
    return MushcoreScalar(m_value);
}

void
GameConfigDefU32::ValueSet(const MushcoreScalar& inValue)
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
GameConfigDefU32::FromPostRetrieve(const string& inName, const string& inData)
{
    bool found=false;
    MushcoreRegExp re("&"+inName+"=([^&$]+)");
    MushcoreRegExp::tMatches matches;
    if (re.Search(matches, inData))
    {
        MUSHCOREASSERT(matches.size() == 1);
        istringstream valueStream(matches[0]);
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
GameConfigDefU32::WebInputPrint(ostream& ioOut, const string& inName)
{
#ifdef MUSHWARE_USE_MUSTL
    ioOut << "<input name=\"" << MushcoreUtil::MakeWebSafe(inName) << "\" type=\"text\" size=\"6\" value=\"" << MushcoreUtil::MakeWebSafe(m_value) << "\">" << endl;
#endif
}

// -----

GameConfigDefString::GameConfigDefString(const string& inValue, const string& inMenu) :
    m_value(inValue),
    m_menu(inMenu)
{
}

GameConfigDefString::~GameConfigDefString()
{
}

const MushcoreScalar
GameConfigDefString::ValueGet(void) const
{
    return MushcoreScalar(m_value);
}

void
GameConfigDefString::ValueSet(const MushcoreScalar& inValue)
{
    m_value = inValue.StringGet();
}

bool
GameConfigDefString::FromPostRetrieve(const string& inName, const string& inData)
{
    bool found=false;
    MushcoreRegExp re("&"+inName+"=([^&$]*)");
    MushcoreRegExp::tMatches matches;
    if (re.Search(matches, inData))
    {
        MUSHCOREASSERT(matches.size() == 1);

        m_value=MushcoreUtil::RemoveMeta(matches[0]);

        found=true;
    }
    return found;
}

void
GameConfigDefString::WebInputPrint(ostream& ioOut, const string& inName)
{

    if (m_menu.size() == 0)
    {
        ioOut << "<input name=\"" << MushcoreUtil::MakeWebSafe(inName) << "\" type=\"text\" size=\"20\" value=\"" << MushcoreUtil::MakeWebSafe(m_value) << "\">" << endl;
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

const MushcoreScalar
GameConfigDefPassword::ValueGet(void) const
{
    return MushcoreScalar(m_value);
}

void
GameConfigDefPassword::ValueSet(const MushcoreScalar& inValue)
{
    m_value = inValue.StringGet();
}

bool
GameConfigDefPassword::FromPostRetrieve(const string& inName, const string& inData)
{
    bool found=false;
    MushcoreRegExp re("&"+inName+"=([^&$]*)");
    MushcoreRegExp::tMatches matches;
    if (re.Search(matches, inData))
    {
        MUSHCOREASSERT(matches.size() == 1);
        string newValue=MushcoreUtil::RemoveMeta(matches[0]);
        if (newValue != "******")
        {
            m_value=MushcoreUtil::RemoveMeta(newValue);
            found=true;
        }
    }
    return found;
}

void
GameConfigDefPassword::WebInputPrint(ostream& ioOut, const string& inName)
{
    ioOut << "<input name=\"" << MushcoreUtil::MakeWebSafe(inName) << "\" type=\"password\" size=\"20\" value=\"";
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

const MushcoreScalar
GameConfigDefBool::ValueGet(void) const
{
    return MushcoreScalar(m_value);
}

void
GameConfigDefBool::ValueSet(const MushcoreScalar& inValue)
{
    m_value = inValue.BoolGet();
}

bool
GameConfigDefBool::FromPostRetrieve(const string& inName, const string& inData)
{
    bool found=false;
    MushcoreRegExp re("&"+inName+"=([^&$]+)");
    MushcoreRegExp::tMatches matches;
    if (re.Search(matches, inData))
    {
        MUSHCOREASSERT(matches.size() == 1);
        istringstream valueStream(matches[0]);
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
GameConfigDefBool::WebInputPrint(ostream& ioOut, const string& inName)
{
    ioOut << "<input name=\"" << MushcoreUtil::MakeWebSafe(inName) << "\" type=\"checkbox\" ";
    if (m_value) ioOut << "checked ";
    ioOut << "value=\"1\">" << endl;
    ioOut << "<input name =\"" << MushcoreUtil::MakeWebSafe(inName) << "\" type=\"hidden\" value=\"0\"" << endl;
}

// -----

void
GameConfigDef::SelectPrologue(ostream& ioOut, const string& inName)
{
    ioOut << "<select name=\"" << MushcoreUtil::MakeWebSafe(inName) << "\">" << endl;
}

void
GameConfigDef::SelectOption(ostream& ioOut, const string& inName, const string& inValue, bool inSelected)
{
    ioOut << "<option ";
    if (inSelected) ioOut << "selected ";
    ioOut << "value=\"" << MushcoreUtil::MakeWebSafe(inValue) << "\">";
    ioOut << MushcoreUtil::MakeWebSafe(inName);
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


