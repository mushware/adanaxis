//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLState.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } wlqHuRRZqpfZYwL14lhh0Q
/*
 * $Id: GLState.cpp,v 1.15 2005/04/10 00:09:22 southa Exp $
 * $Log: GLState.cpp,v $
 * Revision 1.15  2005/04/10 00:09:22  southa
 * Registration
 *
 * Revision 1.14  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.13  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:29  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/01/20 10:45:23  southa
 * Singleton tidying
 *
 * Revision 1.10  2003/01/17 13:30:37  southa
 * Source conditioning and build fixes
 *
 * Revision 1.9  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.8  2003/01/12 17:32:50  southa
 * Mushcore work
 *
 * Revision 1.7  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.6  2002/12/29 20:59:53  southa
 * More build fixes
 *
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

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLState::tBlendType GLState::m_blendState=GLState::kBlendInvalid;
tVal GLState::m_lightingAlpha = 1.0;
GLState::tModulationType GLState::m_modulateState=GLState::kModulationInvalid;
GLState::tDepthType GLState::m_depthState=GLState::kDepthInvalid;
GLState::tDisplayQuality GLState::m_displayQuality=GLState::kQualityNotSet;
bool GLState::m_useLighting=true;
bool GLState::m_textureEnabled=false;
bool GLState::m_useMipMap=true;
GLuint GLState::m_boundTexture=0;

void
GLState::ResolveDisplayQuality(void)
{
    string displayQuality("high");
    
    const MushcoreScalar *pScalar;    
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "DISPLAY_QUALITY"))
    {
        displayQuality = pScalar->StringGet();
    }
    
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
        throw(MushcoreCommandFail("Bad value for DISPLAY_QUALITY: should be low, medium or high"));
    }
}
