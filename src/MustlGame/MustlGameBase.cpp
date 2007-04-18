//%Header {
/*****************************************************************************
 *
 * File: src/MustlGame/MustlGameBase.cpp
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
//%Header } Px30g4QooRuYKBm7/dJSRQ
/*
 * $Id: MustlGameBase.cpp,v 1.7 2006/06/01 15:39:56 southa Exp $
 * $Log: MustlGameBase.cpp,v $
 * Revision 1.7  2006/06/01 15:39:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:20  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/07 11:14:15  southa
 * Snapshot fixes
 *
 * Revision 1.4  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.3  2004/01/01 21:15:46  southa
 * Created XCode project
 *
 * Revision 1.2  2003/10/06 22:42:04  southa
 * Include fixes
 *
 * Revision 1.1  2003/10/06 22:22:38  southa
 * Moved from Game to MustlGame
 *
 * Revision 1.24  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.23  2003/08/21 23:08:42  southa
 * Fixed file headers
 *
 * Revision 1.22  2003/01/20 10:45:25  southa
 * Singleton tidying
 *
 * Revision 1.21  2003/01/13 14:31:57  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.20  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.19  2003/01/07 17:13:41  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.18  2002/12/29 20:59:54  southa
 * More build fixes
 *
 * Revision 1.17  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.16  2002/12/13 01:07:25  southa
 * Mustl work
 *
 * Revision 1.15  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.14  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.13  2002/11/28 15:33:31  southa
 * Pass MustlGameBase status over link
 *
 * Revision 1.12  2002/11/28 15:14:13  southa
 * Multiplayer setup timing
 *
 * Revision 1.11  2002/11/28 12:05:45  southa
 * Server name work
 *
 * Revision 1.10  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.9  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
 * Revision 1.8  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.7  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 * Revision 1.6  2002/11/24 23:18:16  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.4  2002/11/23 17:23:44  southa
 * Sleep in setup
 *
 * Revision 1.3  2002/11/23 15:23:33  southa
 * Fixed network orders for win32
 *
 * Revision 1.2  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.1  2002/11/21 18:06:17  southa
 * Non-blocking network connection
 *
 */

#include "MustlGameBase.h"

#include "MustlGameSTL.h"

#include "mushMustl.h"
#include "mushGL.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MustlGameBase::MustlGameBase(const string& inName) :
    m_name(inName),
    m_status(kStatusInvalid),
    m_isImage(false)
{
    m_creationMsec = dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl()).MillisecondsGet();
}

const string
MustlGameBase::StatusWebStringGet(void) const
{
    switch (m_status)
    {
        case kStatusInvalid:
        default:
            return "<font class=\"bgred\">INVALID</font>";

        case kStatusTesting:
            return "<font class=\"bgyellow\">TESTING</font>";
            
        case kStatusOK:
            return "<font class=\"bggreen\">OK</font>";

        case kStatusNoServer:
            return "<font class=\"bgred\">NO SERVER</font>";
    }
}

void
MustlGameBase::HandleNameEnd(MushcoreXML& inXML)
{
    m_name = inXML.TopData();
}

void
MustlGameBase::HandleStatusEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    const char *failMessage="Bad format for status.  Should be <status>3</status>";
    U32 value;
    if (!(data >> value)) inXML.Throw(failMessage);
    m_status = static_cast<tStatus>(value);
}

void
MustlGameBase::NullHandler(MushcoreXML& inXML)
{
}

void
MustlGameBase::Pickle(ostream& inOut, const string& inPrefix) const
{
    inOut << inPrefix << "<name>" << MustlUtils::MakeXMLSafe(m_name) << "</name>" << endl;
    inOut << inPrefix << "<status>" << m_status << "</status>" << endl;
}

void
MustlGameBase::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["name"] = &MustlGameBase::NullHandler;
    m_endTable[kPickleData]["name"] = &MustlGameBase::HandleNameEnd;
    m_startTable[kPickleData]["status"] = &MustlGameBase::NullHandler;
    m_endTable[kPickleData]["status"] = &MustlGameBase::HandleStatusEnd;
    m_pickleState=kPickleData;
}

void
MustlGameBase::UnpickleEpilogue(void)
{
    m_startTable.clear();
    m_endTable.clear();
}

void
MustlGameBase::Unpickle(MushcoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
MustlGameBase::XMLStartHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p2 = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p2 != m_startTable[m_pickleState].end())
    {
        (this->*p2->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << "> in Def.  Potential matches are";
ElementFunctionMap::iterator p = m_startTable[m_pickleState].begin();
        while (p != m_startTable[m_pickleState].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
MustlGameBase::XMLEndHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p2 = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p2 != m_endTable[m_pickleState].end())
    {
        (this->*p2->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << "> in Def.  Potential matches are";
ElementFunctionMap::iterator p = m_endTable[m_pickleState].begin();
        while (p != m_endTable[m_pickleState].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
MustlGameBase::XMLDataHandler(MushcoreXML& inXML)
{
}

