/*
 * $Id: GLUtils.h,v 1.5 2002/05/31 15:18:16 southa Exp $
 * $Log: GLUtils.h,v $
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
    static void OrthoPrologue(void);
    static void OrthoEpilogue(void);
    static void CheckGLError(void);
    static void StandardInit(void);
    static void GameInit(void);
    static void DisplayPrologue(void);
    static void DisplayEpilogue(void);
    static void ClearScreen(void);
    static void SetColour(float inRed, float inGreen, float inBlue);
    static void DrawRectangle(tVal inX1, tVal inY1, tVal inX2, tVal inY2);
    static void DrawTriangle(tVal inX1, tVal inY1, tVal inX2, tVal inY2, tVal inX3, tVal inY3);
    static void RasterPos(tVal inX, tVal inY);
    static void BitmapText(const string& inStr);
    static void DrawSprite(const GLTexture& inTex, tVal inX, tVal inY);
    static void DrawRotatedSprite(const GLTexture& inTex, tVal inX, tVal inY, tVal inAngle);
    static void PostRedisplay(void);
    
private:
    static void SafetyHandler(void);
};
