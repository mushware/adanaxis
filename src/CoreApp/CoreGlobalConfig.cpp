/*
 * $Id: CoreGlobalConfig.cpp,v 1.1 2002/05/28 13:07:04 southa Exp $
 * $Log: CoreGlobalConfig.cpp,v $
 * Revision 1.1  2002/05/28 13:07:04  southa
 * Command parser extensions and TIFF loader
 *
 */

#include "CoreGlobalConfig.h"
#include "CoreInstaller.h"
#include "CoreEnv.h"

CoreGlobalConfig *CoreGlobalConfig::m_instance=NULL;

CoreInstaller
CoreGlobalConfig(CoreGlobalConfig::Install);

void
CoreGlobalConfig::Install(void)
{
    CoreEnv::Instance().PushConfig(Instance());
}
