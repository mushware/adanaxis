//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalTraits.cpp
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
//%Header } +c2UT584Rh9rdrA9nOGaYw
/*
 * $Id: InfernalTraits.cpp,v 1.6 2006/06/29 10:12:34 southa Exp $
 * $Log: InfernalTraits.cpp,v $
 * Revision 1.6  2006/06/29 10:12:34  southa
 * 64 bit compatibility fixes
 *
 * Revision 1.5  2006/06/01 15:39:07  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:06  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.2  2004/01/01 21:15:46  southa
 * Created XCode project
 *
 * Revision 1.1  2003/10/04 15:32:12  southa
 * Module split
 *
 * Revision 1.22  2003/10/04 12:23:03  southa
 * File renaming
 *
 * Revision 1.21  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.20  2003/08/21 23:08:57  southa
 * Fixed file headers
 *
 * Revision 1.19  2003/02/05 18:49:52  southa
 * Build fixes
 *
 * Revision 1.18  2003/01/20 10:45:27  southa
 * Singleton tidying
 *
 * Revision 1.17  2003/01/13 14:32:01  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.16  2003/01/12 17:32:57  southa
 * Mushcore work
 *
 * Revision 1.15  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.14  2003/01/07 17:13:43  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.13  2002/12/29 20:59:57  southa
 * More build fixes
 *
 * Revision 1.12  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 * Revision 1.10  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.9  2002/10/14 15:13:40  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.8  2002/08/27 08:56:27  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/08 14:22:03  southa
 * Rotated desks
 *
 * Revision 1.5  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.3  2002/06/04 20:27:37  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.2  2002/06/04 17:02:11  southa
 * More work
 *
 * Revision 1.1  2002/06/04 14:12:25  southa
 * Traits loader first stage
 *
 */

#include "InfernalTraits.h"

#include "InfernalData.h"
#include "InfernalSTL.h"

using namespace Mushware;
using namespace std;

void
InfernalTraits::Verify(void)
{
    if (!m_traitsValid) RebuildTraits();
    if (!m_traitsValid)
    {
        string message("Trait with bases");
        for (U32 i=0; i<m_baseNames.size(); ++i)
        {
            message+=" ";
            message+=m_baseNames[i];
        }
        message+=" failed to build because";
        message+=m_failMessage;
        message+=" were missing";
        throw(MushcoreRequestFail(message));
    }
}

void
InfernalTraits::RebuildTraits(void) const
{
    MUSHCOREASSERT(!m_traitsValid);
    m_baseTraits.resize(0);
    m_failMessage.erase();
    bool success=true;
    for (U32 i=0;i<m_baseNames.size(); ++i)
    {
        try
        {
            m_baseTraits.push_back(InfernalData::Sgl().TraitsGet(m_baseNames[i]));
        }
        catch (MushcoreDataFail& e)
        {
            success=false;
            m_failMessage+=" ";
            m_failMessage+=e.what();
        }
    }
    m_traitsValid=success;
}


void
InfernalTraits::HandleBaseEnd(MushcoreXML& inXML)
{
    string inStr(inXML.TopData());
    string::size_type start=0;
    string::size_type end=0;
    while (end != string::npos && start < inStr.size())
    {
        end=inStr.find(',', start);
        m_baseNames.push_back(inStr.substr(start,end-start));
        start=end+1;
    }
}

void
InfernalTraits::HandleTraitsEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
}

void
InfernalTraits::NullHandler(MushcoreXML& inXML)
{
}

void
InfernalTraits::Pickle(ostream& inOut, const string& inPrefix) const
{
    if (m_baseNames.size() != 0)
    {
        inOut << inPrefix << "<base>";
        for (U32 i=0; i<m_baseNames.size(); i++)
        {
            inOut << m_baseNames[i];
            if (i+1 < m_baseNames.size()) inOut << ",";
        }
        inOut << "</base>" << endl;
    }
}

void
InfernalTraits::UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["base"] = &InfernalTraits::NullHandler;
    m_endTable[kPickleData]["base"] = &InfernalTraits::HandleBaseEnd;
    m_endTable[kPickleData]["traits"] = &InfernalTraits::HandleTraitsEnd;
    m_pickleState=kPickleData;
    m_baseNames.clear();
}

void
InfernalTraits::UnpickleEpilogue(void)
{
    m_startTable.clear();
    m_endTable.clear();
}

void
InfernalTraits::Unpickle(MushcoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
InfernalTraits::XMLStartHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p2 = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p2 != m_startTable[m_pickleState].end())
    {
        (this->*p2->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << "> in Traits.  Potential matches are";
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
InfernalTraits::XMLEndHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p2 = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p2 != m_endTable[m_pickleState].end())
    {
        (this->*p2->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << "> in Traits.  Potential matches are";
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
InfernalTraits::XMLDataHandler(MushcoreXML& inXML)
{
}

