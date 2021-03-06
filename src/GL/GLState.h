//%includeGuardStart {
#ifndef GLSTATE_H
#define GLSTATE_H
//%includeGuardStart } oLtZc7hFVhqjAxvAzi9lSQ
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLState.h
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
//%Header } OW7ml+OGtAGYM/j7iIB5Pg

/*
 * $Id: GLState.h,v 1.18 2006/06/01 15:38:53 southa Exp $
 * $Log: GLState.h,v $
 * Revision 1.18  2006/06/01 15:38:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.17  2005/09/06 12:15:35  southa
 * Texture and rendering work
 *
 * Revision 1.16  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.15  2005/04/10 00:09:22  southa
 * Registration
 *
 * Revision 1.14  2005/02/13 22:44:06  southa
 * Tesseract stuff
 *
 * Revision 1.13  2004/03/07 12:05:56  southa
 * Rendering work
 *
 * Revision 1.12  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.11  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.10  2003/08/21 23:08:29  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/01/12 17:32:50  southa
 * Mushcore work
 *
 * Revision 1.8  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/12/04 15:39:57  southa
 * Multiplayer work
 *
 * Revision 1.6  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.5  2002/10/17 15:50:58  southa
 * Config saving, pause and quit
 *
 * Revision 1.4  2002/10/14 13:03:00  southa
 * Display std::list test
 *
 * Revision 1.3  2002/10/13 12:26:46  southa
 * Facetised std::map rendering
 *
 * Revision 1.2  2002/10/12 17:34:20  southa
 * Wall edges
 *
 * Revision 1.1  2002/10/12 15:24:58  southa
 * Facet renderer
 *
 */

#include "GLStandard.h"

class GLState
{
public:
    enum tBlendType
    {
        kBlendInvalid,
        kBlendNone,
        kBlendTransparent,
        kBlendSolid,
        kBlendLine,
        kBlendAccumulate
    };

    enum tModulationType
    {
        kModulationInvalid,
        kModulationNone,
        kModulationColour,
        kModulationLighting,
        kModulationInvalidated
    };

    enum tDepthType
    {
        kDepthInvalid,
        kDepthNone,
        kDepthTest
    };

    enum tDisplayQuality
    {
        kQualityInvalid,
        kQualityNotSet,
        kQualityLow,
        kQualityMedium,
        kQualityHigh
    };

    static void ColourSet(GLfloat inRed, GLfloat inGreen, GLfloat inBlue);
    static void ColourSet(GLfloat inRed, GLfloat inGreen, GLfloat inBlue, GLfloat inAlpha);

    
    static void BlendSet(tBlendType inType);
    static void AmbientLightSet(Mushware::tVal inAmbient);
    static void LightingAlphaSet(Mushware::tVal inAlpha);
    static void ModulationSet(tModulationType inType);
    static void DepthSet(tDepthType inType);
    static void UseLightingSet(bool inValue);
    static void Reset(void);
    static void TextureParamsReset(void);
    static tDisplayQuality DisplayQualityGet(void);
    static void BindTexture(GLuint inHandle);
    static void TextureEnable(void);
    static void TextureDisable(void);
    static bool UseMipMap(void) { return m_useMipMap; }
    static void ContextReset(void);
private:
    static void ResolveDisplayQuality(void);
        
    static tBlendType m_blendState;
    static Mushware::tVal m_lightingAlpha;
    static tModulationType m_modulateState;
    static tDepthType m_depthState;
    static tDisplayQuality m_displayQuality;
    static bool m_useLighting;
    static bool m_textureEnabled;
    static bool m_useMipMap;

    static GLuint m_boundTexture;
};

inline void
GLState::ColourSet(GLfloat inRed, GLfloat inGreen, GLfloat inBlue)
{
    glColor3f(inRed, inGreen, inBlue);
}

inline void
GLState::ColourSet(GLfloat inRed, GLfloat inGreen, GLfloat inBlue, GLfloat inAlpha)
{
    glColor4f(inRed, inGreen, inBlue, inAlpha);
}

inline void
GLState::BlendSet(tBlendType inValue)
{
    if (m_blendState != inValue)
    {
        switch (inValue)
        {
            case kBlendTransparent:
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glEnable(GL_BLEND);
                break;
                
            case kBlendAccumulate:
                glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                glEnable(GL_BLEND);
                break;
                
            case kBlendLine:
            {
                if (m_displayQuality != kQualityLow)
                {
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glEnable(GL_BLEND);
                }
                else
                {
                    glDisable(GL_BLEND);
                }
            }
            break;

            case kBlendNone:
                glDisable(GL_BLEND);
                break;

            case kBlendSolid:
                glDisable(GL_BLEND);
                break;

            default:
                throw(MushcoreLogicFail("Invalid value to GLState::BlendSet"));
                break;
        }
        m_blendState = inValue;
    }
}

inline void
GLState::AmbientLightSet(Mushware::tVal inAmbient)
{
    GLfloat ambient[4]={inAmbient, inAmbient, inAmbient, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
}

inline void
GLState::LightingAlphaSet(Mushware::tVal inAlpha)
{
    m_lightingAlpha = inAlpha;
    m_modulateState = kModulationInvalidated;
}

inline void
GLState::ModulationSet(tModulationType inValue)
{
    if (m_modulateState != inValue)
    {
        switch (inValue)
        {
            case kModulationNone:
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                glDisable(GL_LIGHTING);
                break;

            case kModulationColour:
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                glDisable(GL_LIGHTING);
                break;

            case kModulationLighting:
                if (m_useLighting)
                {
                    GLfloat ambient[4]={1.0,1.0,1.0,1.0};
                    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);

                    GLfloat specular[4]={1.0,1.0,1.0,1.0};
                    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

                    GLfloat diffuse[4]={0.1,0.1,0.1,m_lightingAlpha};
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

                    glMaterialf(GL_FRONT, GL_SHININESS, 128);

                    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                    glEnable(GL_LIGHTING);
                    glNormal3f(0,0,1);
                }
                else
                {
                    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                    glDisable(GL_LIGHTING);
                    ColourSet(1,1,1,1);
                }
                break;

            default:
                throw(MushcoreLogicFail("Invalid value to GLState::ModulationSet"));
                break;
        }
        m_modulateState=inValue;
    }
}

inline void
GLState::DepthSet(tDepthType inValue)
{
    if (m_depthState != inValue)
    {
        switch (inValue)
        {
            case kDepthNone:
                glDisable(GL_DEPTH_TEST);
                break;

            case kDepthTest:
                glDepthFunc(GL_LEQUAL);
                glEnable(GL_DEPTH_TEST);
                break;

            default:
                throw(MushcoreLogicFail("Invalid value to GLState::DepthSet"));
                break;
        }
        m_depthState=inValue;
    }
}

inline GLState::tDisplayQuality
GLState::DisplayQualityGet(void)
{
    if (m_displayQuality == kQualityNotSet)
    {
        ResolveDisplayQuality();
    }
    return m_displayQuality;
}

inline void
GLState::TextureParamsReset(void)
{
    if (m_useMipMap)
    {
        switch (DisplayQualityGet())
        {
            case kQualityLow:
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
                break;

            case kQualityMedium:
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                break;

            case kQualityHigh:
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                break;

            default:
                throw(MushcoreLogicFail("Bad value for m_displayQuality"));
        }
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    }
}

inline void
GLState::Reset(void)
{
    TextureParamsReset();
    
    switch (DisplayQualityGet())
    {
        case kQualityLow:
            break;
            
        case kQualityMedium:    
            break;

        case kQualityHigh:
            glEnable(GL_POINT_SMOOTH);
            glEnable(GL_LINE_SMOOTH);
            break;

        default:
            throw(MushcoreLogicFail("Bad value for m_displayQuality"));
    }
    glLineWidth(1);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glDisable(GL_POLYGON_SMOOTH);
    m_depthState=kDepthInvalid;
    DepthSet(kDepthNone);
    m_modulateState=kModulationInvalid;
    ModulationSet(kModulationNone);
    m_blendState=kBlendInvalid;
    BlendSet(kBlendNone);
    glEnable(GL_TEXTURE_2D);
    m_textureEnabled=true;
    m_boundTexture=0;
    glEnableClientState(GL_VERTEX_ARRAY); // Always enabled
    glEnableClientState(GL_TEXTURE_COORD_ARRAY); // Always enabled
    glEnableClientState(GL_NORMAL_ARRAY); // Always enabled
}

inline void
GLState::UseLightingSet(bool inValue)
{
    m_useLighting=inValue;
}

inline void
GLState::BindTexture(GLuint inHandle)
{
    if (inHandle != m_boundTexture)
    {
        glBindTexture(GL_TEXTURE_2D, inHandle);
        m_boundTexture = inHandle;
    }
}

inline void
GLState::ContextReset(void)
{
    m_boundTexture = ~0;
}    

inline void
GLState::TextureDisable(void)
{
    if (m_textureEnabled)
    {
        glDisable(GL_TEXTURE_2D);
        m_textureEnabled=false;
    }
}

inline void
GLState::TextureEnable(void)
{
    if (!m_textureEnabled)
    {
        glEnable(GL_TEXTURE_2D);
        m_textureEnabled=true;
    }
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
