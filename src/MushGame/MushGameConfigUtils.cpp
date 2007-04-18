//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameConfigUtils.cpp
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
//%Header } YGO3AZcyE5CiPfW6A0Ybdw
/*
 * $Id: MushGameConfigUtils.cpp,v 1.3 2006/07/26 16:37:23 southa Exp $
 * $Log: MushGameConfigUtils.cpp,v $
 * Revision 1.3  2006/07/26 16:37:23  southa
 * Options menu
 *
 * Revision 1.2  2006/06/01 15:39:20  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/06/14 20:39:41  southa
 * Adanaxis work
 *
 */

#include "MushGameConfigUtils.h"

using namespace Mushware;
using namespace std;

void
MushGameConfigUtils::ConfigAcquire(MushGameConfigBase *inpConfig)
{
    MUSHCOREASSERT(inpConfig != NULL);
    
    const MushcoreScalar *pScalar = NULL; 
    
    U32 currentVersion = 0;
    
    {
        /* Get current config version.  Use the input object to create an object
         * of the same type
        */  
        MushGameConfigBase *tempConfig = dynamic_cast<MushGameConfigBase *>(inpConfig->AutoCreate());
        if (tempConfig == NULL)
        {
            throw MushcoreLogicFail("Wrong type passed to AcquireConfig");
        }
        currentVersion = tempConfig->Version();
        delete tempConfig;
    }
    
    try
    {
        if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "CONFIG_FILENAME"))
        {
            if (!inpConfig->AutoFileIfExistsLoad(pScalar->StringGet()))
            {
                MushcoreLog::Sgl().InfoLog() << "Creating new configuration file '" << pScalar->StringGet() << "'" << endl;
                inpConfig->ToDefaultSet();
            }
            if (inpConfig->Version() != currentVersion)
            {
                throw MushcoreDataFail("Incompatible configuration file version - discarding");
            }
        }
    }
    catch (MushcoreFail& e)
    {
        MushcoreLog::Sgl().ErrorLog() << e.what() << endl;
        inpConfig->ToDefaultSet();
    }

    // Safe mode is pseudo-config - not saved
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "SAFE_MODE"))
    {
        if (pScalar->U32Get())
        {
            inpConfig->SafeModeSet(1);
        }
    }
    else
    {
        inpConfig->SafeModeSet(0);
    }
}
