#ifndef GLUTILS_H
#define GLUTILS_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/



/*
 * $Id: GLUtils.h,v 1.21 2002/08/08 13:39:09 southa Exp $
 * $Log: GLUtils.h,v $
 * Revision 1.21  2002/08/08 13:39:09  southa
 * Text rendering
 *
 * Revision 1.20  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.19  2002/08/01 16:47:10  southa
 * First multi-box collsion checking
 *
 * Revision 1.18  2002/07/31 16:27:15  southa
 * Collision checking work
 *
 * Revision 1.17  2002/07/19 17:51:10  southa
 * Texture tweaks
 *
 * Revision 1.16  2002/07/19 16:25:21  southa
 * Texture tweaks
 *
 * Revision 1.15  2002/07/19 15:44:40  southa
 * Graphic optimisations
 *
 * Revision 1.14  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 * Revision 1.13  2002/07/08 14:22:02  southa
 * Rotated desks
 *
 * Revision 1.12  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.11  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 * Revision 1.10  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.9  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.8  2002/06/05 12:28:05  southa
 * Map rendered using traits
 *
 * Revision 1.7  2002/06/04 17:02:24  southa
 * More work
 *
 * Revision 1.6  2002/06/02 16:41:18  southa
 * Rotated sprite plotting
 *
 * Revision 1.5  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.4  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.3  2002/05/28 13:07:01  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.2  2002/05/27 12:58:43  southa
 * GameContract and global configs added
 *
 * Revision 1.1  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 */

#include "GLStandard.h"

class GLTexture;
class GLRectangle;
class GLPoint;

class GLUtils
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
    
    enum tDisplayQuality
    {
        kQualityInvalid,
        kQualityNotSet,
        kQualityLow,
        kQualityMedium,
        kQualityHigh
    };

    GLUtils(): m_x(0), m_y(0) {}
    void SetPosition(tVal inX, tVal inY) {m_x=inX;m_y=inY;}
    void MoveTo(tVal inX, tVal inY);
    void MoveRelative(tVal inX, tVal inY);
    void MoveToEdge(tVal inX, tVal inY);

    static void Vertex(tVal inX, tVal inY) { glVertex2f(inX, inY); }
    static void IdentityPrologue(void);
    static void IdentityEpilogue(void);
    static void OrthoPrologue(void);
    static void OrthoEpilogue(void);
    static const GLPoint ScreenSizeGet(void);
    static const GLPoint ScreenRatiosGet(void); // Screensize / longest axis
    static tVal LongestScreenAxis(void);
    static void OrthoLookAt(tVal inX, tVal inY, tVal inAngle);
    static void CheckGLError(void);
    static void DisplayPrologue(void);
    static void DisplayEpilogue(void);
    static void ClearScreen(void);
    static void ColourSet(float inRed, float inGreen, float inBlue);
    static void ColourSet(tVal inRed, tVal inGreen, tVal inBlue, tVal inAlpha)
    {
        glColor4f(inRed, inGreen, inBlue, inAlpha);
    }
    static void DrawRectangle(tVal inX1, tVal inY1, tVal inX2, tVal inY2);
    static void DrawTriangle(tVal inX1, tVal inY1, tVal inX2, tVal inY2, tVal inX3, tVal inY3);
    static void RasterPos(tVal inX, tVal inY);
    static void BitmapText(const string& inStr);
    static void DrawSprite(const GLTexture& inTex, tVal inX, tVal inY);
    static void DrawSprite(const GLTexture& inTex);
    static void DrawSprite(const GLTexture& inTex, const GLRectangle& inRectangle);
    static void DrawRotatedSprite(const GLTexture& inTex, tVal inX, tVal inY, tVal inAngle);
    static void PostRedisplay(void);
    static void Scale(tVal inXScale, tVal inYScale, tVal inZScale);
    static void RotateAboutZ(tVal inAngle);
    static void BlendSet(tBlendType inType);
    static void ModulateSet(bool inType);
    static void Reset(void);
    static void TextureParamsReset(void);
    static tDisplayQuality DisplayQualityGet(void);
    static void PolygonSmoothingSet(bool inValue);
    
private:            
    static void SafetyHandler(void);
    tVal m_x;
    tVal m_y;

    static tBlendType m_blendState;
    static bool m_modulateState;
    static tDisplayQuality m_displayQuality;
    static bool m_polygonSmoothing;
};
#endif
