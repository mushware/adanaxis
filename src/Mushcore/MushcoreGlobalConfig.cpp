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
 * $Id: MushcoreGlobalConfig.cpp,v 1.3 2003/01/15 13:27:32 southa Exp $
 * $Log: MushcoreGlobalConfig.cpp,v $
 * Revision 1.3  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.2  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.8  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/30 14:41:15  southa
 * GameData and loadtilemap command
 *
 * Revision 1.1  2002/05/28 13:07:04  southa
 * Command parser extensions and TIFF loader
 *
 */

#include "MushcoreGlobalConfig.h"

#include "MushcoreDestroySingleton.h"
#include "MushcoreEnv.h"
#include "MushcoreInstaller.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushcoreGlobalConfig);

MushcoreInstaller
MushcoreGlobalConfig(MushcoreGlobalConfig::Install);

void
MushcoreGlobalConfig::Install(void)
{
    MushcoreEnv::Instance().PushConfig(Instance());
}

void
MushcoreGlobalConfig::NullFunction(void)
{
}    
