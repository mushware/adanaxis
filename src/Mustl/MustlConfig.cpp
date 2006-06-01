//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfig.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } uMubA2sxALtRoI3hxMNM8Q
/*
 * $Id: MustlConfig.cpp,v 1.14 2005/05/19 13:02:17 southa Exp $
 * $Log: MustlConfig.cpp,v $
 * Revision 1.14  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.13  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.12  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.11  2003/08/21 23:09:21  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.9  2003/01/17 12:20:40  southa
 * Fixed auto_ptr duplication
 *
 * Revision 1.8  2003/01/17 00:41:03  southa
 * Configuration updates from POST data
 *
 * Revision 1.7  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.6  2003/01/14 20:46:11  southa
 * Post data handling
 *
 * Revision 1.5  2003/01/14 17:38:21  southa
 * Mustl web configuration
 *
 * Revision 1.4  2003/01/14 12:40:10  southa
 * Moved ConfigDefs into Mustl
 *
 * Revision 1.3  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 * Revision 1.2  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.1  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 */

#include "MustlConfig.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

MustlConfig *MustlConfig::m_instance = NULL;

MushcoreInstaller MustlConfigInstaller(MustlConfig::Install);

MustlConfig::MustlConfig()
{
}

MustlConfig::~MustlConfig()
{
}

MushcoreScalar
MustlConfig::Get(const string& inName) const
{
    return MushcoreData<MustlConfigDef>::Sgl().Get(inName)->ValueGet();
}

bool
MustlConfig::GetIfExists(MushcoreScalar& outScalar, const std::string& inName) const
{
    MustlConfigDef *pConfigDef;
    if (MushcoreData<MustlConfigDef>::Sgl().GetIfExists(pConfigDef, inName))
    {
        outScalar = pConfigDef->ValueGet();
        return true;
    }
    return false;
}

void
MustlConfig::PostDataHandle(const string& inData)
{
    bool found=false;
    string failStr;
    
    MushcoreData<MustlConfigDef>::tMapIterator endValue=MushcoreData<MustlConfigDef>::Sgl().End();

    for (MushcoreData<MustlConfigDef>::tMapIterator p=MushcoreData<MustlConfigDef>::Sgl().Begin(); p != endValue; ++p)
    {
        try
        {
            if (p->second->FromPostRetrieve(p->first, inData))
            {
                found=true;
            }
        }
        catch (MushcoreNonFatalFail& e)
        {
            failStr += " ";
            failStr += e.what();
        }
    }

    if (found)
    {
        UpdateHandlersCall();
    }
    if (failStr != "")
    {
        throw(MustlFail("Bad parameters:"+failStr));
    }
}

void
MustlConfig::UpdateHandlerAdd(tUpdateHandler inHandler)
{
    m_updateHandlers.push_back(inHandler);
}

void
MustlConfig::UpdateHandlersCall(void) const
{
    list<tUpdateHandler>::const_iterator endValue = m_updateHandlers.end();
    for (list<tUpdateHandler>::const_iterator p = m_updateHandlers.begin(); p != endValue; ++p)
    {
        (*p)();
    }
}

void
MustlConfig::Install(void)
{
    // Add default values to global configuration

    // This function contains details of all mustl variables

    // MUSTL_WEB_PATH      Path to files served by the built-in web server

    // Name of the command used to handle non-mustlonly POST data, i.e. any
    // POST data from HTML forms where the value of the type field doesn't
    // start with the string mustlonly
    MushcoreGlobalConfig::Sgl().Set("MUSTL_POST_HANDLER", "posthandler");
}

void
MustlConfig::NullFunction(void)
{
    MustlConfigDef::NullFunction();
}
