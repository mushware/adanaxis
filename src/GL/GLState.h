#ifndef GLSTATE_H
#define GLSTATE_H

/*
 * $Id$
 * $Log$
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
        kBlendLine
    };

    enum tModulationType
    {
        kModulationInvalid,
        kModulationNone,
        kModulationColour,
        kModulationLighting
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
    static void AmbientLightSet(tVal inAmbient);
    static void ModulationSet(tModulationType inType);
    static void DepthSet(tDepthType inType);
    static void PolygonSmoothingSet(bool inValue);
    static void UseLightingSet(bool inValue);
    static void Reset(void);
    static void TextureParamsReset(void);
    static tDisplayQuality DisplayQualityGet(void);
    static void BindTexture(GLuint inHandle);
    static void TextureEnable(void);
    static void TextureDisable(void);
    
private:
    static void ResolveDisplayQuality(void);
        
    static tBlendType m_blendState;
    static tModulationType m_modulateState;
    static tDepthType m_depthState;
    static tDisplayQuality m_displayQuality;
    static bool m_polygonSmoothing;
    static bool m_useLighting;
    static bool m_textureEnabled;

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
                glDisable(GL_POLYGON_SMOOTH);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glEnable(GL_BLEND);
                break;

            case kBlendLine:
            {
                glDisable(GL_POLYGON_SMOOTH);
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
                glDisable(GL_POLYGON_SMOOTH);
                glDisable(GL_BLEND);
                break;

            case kBlendSolid:
                if (m_polygonSmoothing)
                {
                    // Set up polygon anti-aliasing
                    glEnable(GL_POLYGON_SMOOTH);
                    glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
                    glEnable(GL_BLEND);
                }
                else
                {
                    glDisable(GL_BLEND);
                }
                break;

            default:
                throw(LogicFail("Invalid value to GLState::BlendSet"));
                break;
        }
        m_blendState = inValue;
    }
}

inline void
GLState::AmbientLightSet(tVal inAmbient)
{
    GLfloat ambient[4]={inAmbient, inAmbient, inAmbient, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
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
                    GLfloat ambient[4]={1.0,1.0,1.0,1};
                    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);

                    GLfloat specular[4]={1.0,1.0,1.0,1};
                    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

                    GLfloat diffuse[4]={0.1,0.1,0.1,1};
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
                throw(LogicFail("Invalid value to GLState::ModulationSet"));
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
                throw(LogicFail("Invalid value to GLState::DepthSet"));
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
            throw(LogicFail("Bad value for m_displayQuality"));
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
            throw(LogicFail("Bad value for m_displayQuality"));
    }
    m_depthState=kDepthInvalid;
    DepthSet(kDepthNone);
    m_modulateState=kModulationInvalid;
    ModulationSet(kModulationNone);
    glEnable(GL_TEXTURE_2D);
    m_textureEnabled=true;
    glEnableClientState(GL_VERTEX_ARRAY); // Always enabled
    glEnableClientState(GL_TEXTURE_COORD_ARRAY); // Always enabled
}

inline void
GLState::PolygonSmoothingSet(bool inValue)
{
    m_polygonSmoothing=inValue;
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
#endif
