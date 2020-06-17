//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameConfigUtils.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 4fSKIAE/eFi5HSjWOvpa4A
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
