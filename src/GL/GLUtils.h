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
 * $Id: GLUtils.h,v 1.9 2002/06/20 15:50:30 southa Exp $
 * $Log: GLUtils.h,v $
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

class GLUtils
{
public:
    void SetPosition(tVal inX, tVal inY) {m_x=inX;m_y=inY;}
    void MoveTo(tVal inX, tVal inY);

    static void IdentityPrologue(void);
    static void IdentityEpilogue(void);
    static void OrthoPrologue(void);
    static void OrthoEpilogue(void);
    static void OrthoLookAt(tVal inX, tVal inY, tVal inAngle);
    static void CheckGLError(void);
    // static void StandardInit(void);
    // static void GameInit(void);
    static void DisplayPrologue(void);
    static void DisplayEpilogue(void);
    static void ClearScreen(void);
    static void SetColour(float inRed, float inGreen, float inBlue);
    static void DrawRectangle(tVal inX1, tVal inY1, tVal inX2, tVal inY2);
    static void DrawTriangle(tVal inX1, tVal inY1, tVal inX2, tVal inY2, tVal inX3, tVal inY3);
    static void RasterPos(tVal inX, tVal inY);
    static void BitmapText(const string& inStr);
    static void DrawSprite(const GLTexture& inTex, tVal inX, tVal inY);
    static void DrawSprite(const GLTexture& inTex);
    static void DrawRotatedSprite(const GLTexture& inTex, tVal inX, tVal inY, tVal inAngle);
    static void PostRedisplay(void);
    
private:
    static void SafetyHandler(void);
    tVal m_x;
    tVal m_y;
};
#endif
