/*
 * $Id$
 * $Log$
 */

#include "GLState.h"

GLState::tBlendType GLState::m_blendState=GLState::kBlendInvalid;
GLState::tModulationType GLState::m_modulateState=GLState::kModulationInvalid;
GLState::tDepthType GLState::m_depthState=GLState::kDepthInvalid;
GLState::tDisplayQuality GLState::m_displayQuality=GLState::kQualityNotSet;
bool GLState::m_polygonSmoothing=false;
bool GLState::m_useLighting=true;
bool GLState::m_textureEnabled=false;
GLuint GLState::m_boundTexture=0;

void
GLState::ResolveDisplayQuality(void)
{
    string displayQuality("low");
    CoreEnv::Instance().VariableGetIfExists(displayQuality, "DISPLAY_QUALITY");
    if (displayQuality == "low")
    {
        m_displayQuality = kQualityLow;
    }
    else if (displayQuality == "medium")
    {
        m_displayQuality = kQualityMedium;
    }
    else if (displayQuality == "high")
    {
        m_displayQuality = kQualityHigh;
    }
    else
    {
        throw(CommandFail("Bad value for DISPLAY_QUALITY: should be low, medium or high"));
    }
}