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
 * $Id: MustlConfig.cpp,v 1.10 2003/01/20 10:45:29 southa Exp $
 * $Log: MustlConfig.cpp,v $
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
