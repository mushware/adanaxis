/*
 * $Id$
 * $Log$
 */

#include "GameConfig.h"
#include "mushPlatform.h"

GameConfig *GameConfig::m_instance=NULL;

GameConfig::GameConfig()
{
    m_displayMode=PlatformVideoUtils::Instance().DefaultModeGet();
    CoreEnv::Instance().VariableGetIfExists(m_displayMode, "DISPLAY_MODE");
}

void
GameConfig::DisplayModeSet(U32 inMode)
{
    m_displayMode=inMode;
    // write to disc
}

void
GameConfig::DisplayModeSetDefault(void)
{
    m_displayMode=PlatformVideoUtils::Instance().DefaultModeGet();
    // write to disc
}
