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
 * $Id: GLState.cpp,v 1.5 2002/12/20 13:17:35 southa Exp $
 * $Log: GLState.cpp,v $
 * Revision 1.5  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/12/04 15:39:57  southa
 * Multiplayer work
 *
 * Revision 1.3  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.2  2002/10/17 15:50:58  southa
 * Config saving, pause and quit
 *
 * Revision 1.1  2002/10/12 15:24:58  southa
 * Facet renderer
 *
 */

#include "GLState.h"

using namespace Mushware;
using namespace std;

GLState::tBlendType GLState::m_blendState=GLState::kBlendInvalid;
tVal GLState::m_lightingAlpha = 1.0;
GLState::tModulationType GLState::m_modulateState=GLState::kModulationInvalid;
GLState::tDepthType GLState::m_depthState=GLState::kDepthInvalid;
GLState::tDisplayQuality GLState::m_displayQuality=GLState::kQualityNotSet;
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
