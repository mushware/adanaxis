//%includeGuardStart {
#ifndef GLUTILS_H
#define GLUTILS_H
//%includeGuardStart } 8THyZDfrG+pGVou6WTmP6A
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLUtils.h
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } jKRBe8vPzzL0CzoE/aKrog
/*
 * $Id: GLUtils.h,v 1.47 2006/06/01 15:38:55 southa Exp $
 * $Log: GLUtils.h,v $
 * Revision 1.47  2006/06/01 15:38:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.46  2005/05/20 13:19:00  southa
 * Release work
 *
 * Revision 1.45  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.44  2005/03/25 19:13:48  southa
 * GameDialogue work
 *
 * Revision 1.43  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 * Revision 1.42  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.41  2003/10/04 15:32:08  southa
 * Module split
 *
 * Revision 1.40  2003/10/04 12:22:58  southa
 * File renaming
 *
 * Revision 1.39  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.38  2003/08/21 23:08:33  southa
 * Fixed file headers
 *
 * Revision 1.37  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.36  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.35  2002/12/03 20:28:14  southa
 * Network, player and control work
 *
 * Revision 1.34  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.33  2002/10/15 14:02:30  southa
 * Mode changes
 *
 * Revision 1.32  2002/10/14 15:12:31  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.31  2002/10/12 15:25:11  southa
 * Facet renderer
 *
 * Revision 1.30  2002/10/11 14:01:11  southa
 * Lighting work
 *
 * Revision 1.29  2002/10/08 21:44:09  southa
 * 3D maps
 *
 * Revision 1.28  2002/10/08 17:13:17  southa
 * Tiered maps
 *
 * Revision 1.27  2002/10/07 17:49:45  southa
 * Multiple values per std::map element
 *
 * Revision 1.26  2002/10/07 12:15:36  southa
 * First specular lighting
 *
 * Revision 1.25  2002/10/06 22:09:58  southa
 * Initial lighting test
 *
 * Revision 1.24  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.23  2002/08/09 17:09:02  southa
 * InfernalDialogue added
 *
 * Revision 1.22  2002/08/08 18:20:29  southa
 * Plot on screen of dimension 1.0
 *
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
 * InfernalContract and global configs added
 *
 * Revision 1.1  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 */

#include "GLPoint.h"
#include "GLStandard.h"
#include "GLVector.h"

#include "mushMushMesh.h"

class GLTexture;
class GLRectangle;

class GLUtils
{
public:
    GLUtils(): m_x(0), m_y(0) {}
    void SetPosition(Mushware::tVal inX, Mushware::tVal inY) {m_x=inX;m_y=inY;}
    void MoveTo(Mushware::tVal inX, Mushware::tVal inY);
    void MoveTo(const GLPoint& inPoint) { MoveTo(inPoint.x, inPoint.y); }
    void MoveTo(const Mushware::t2Val& inPoint) { MoveTo(inPoint.X(), inPoint.Y()); }
    void MoveRelative(Mushware::tVal inX, Mushware::tVal inY);
    void MoveToEdge(Mushware::tVal inX, Mushware::tVal inY);

    static void Vertex(Mushware::tVal inX, Mushware::tVal inY) { glVertex2f(inX, inY); }
    static void Vertex(Mushware::tVal inX, Mushware::tVal inY, Mushware::tVal inZ) { glVertex3f(inX, inY, inZ); }
    static void IdentityPrologue(void);
    static void IdentityEpilogue(void);
    static void OrthoPrologue(void);
    static void OrthoEpilogue(void);
    static const GLPoint ScreenSizeGet(void);
    static const GLPoint ScreenRatiosGet(void); // Screensize / longest axis
    static Mushware::tVal ScreenScaleGet(void);
    static Mushware::tVal EyeDistanceGet(void) { return m_eyeDistance; }
    static Mushware::tVal LongestScreenAxis(void);
    static void OrthoLookAt(Mushware::tVal inX, Mushware::tVal inY, Mushware::tVal inAngle);
    static void PerspectiveLookAt(const GLPoint& inPoint, Mushware::tVal inAngle);
    static void PerspectiveLookAt(const GLVector& inCamera, const GLVector& inLookAt, Mushware::tVal inAngle);
    static void StereoPerspectiveLookAt(const GLVector& inCamera, const GLVector& inLookAt, Mushware::tVal inAngle, Mushware::tVal inOffset);
    static void CheckGLError(void);
    static void DisplayPrologue(void);
    static void DisplayEpilogue(void);
    static void ClearScreen(void);

    static void DrawRectangle(Mushware::tVal inX1, Mushware::tVal inY1, Mushware::tVal inX2, Mushware::tVal inY2);
    static void DrawTriangle(Mushware::tVal inX1, Mushware::tVal inY1, Mushware::tVal inX2, Mushware::tVal inY2, Mushware::tVal inX3, Mushware::tVal inY3);
    static void RasterPos(Mushware::tVal inX, Mushware::tVal inY);
    static void BitmapText(const std::string& inStr);
    static void DrawSprite(const GLTexture& inTex, Mushware::tVal inX, Mushware::tVal inY);
    static void DrawSprite(const GLTexture& inTex);
    static void DrawSprite(const GLTexture& inTex, const GLRectangle& inRectangle);
    static void DrawRotatedSprite(const GLTexture& inTex, Mushware::tVal inX, Mushware::tVal inY, Mushware::tVal inAngle);
    static void PostRedisplay(void);
    static void Scale(Mushware::tVal inXScale, Mushware::tVal inYScale, Mushware::tVal inZScale);
    static void RotateAboutZ(Mushware::tVal inAngle);

    static void PushMatrix(void) { glPushMatrix(); }
    static void PopMatrix(void) { glPopMatrix(); }
    static void Translate(const GLVector& inVec) { glTranslatef(inVec.x, inVec.y, inVec.z); }
    static void Flush(void) { glFlush(); }
    static void Decache(void);
    static Mushware::U32 ListContextGet(void) { return m_context; }
    static Mushware::U32 TextureContextGet(void) { return m_context; }

private:            
    static void SafetyHandler(void);
    Mushware::tVal m_x;
    Mushware::tVal m_y;

    static Mushware::tVal m_eyeDistance;
    static Mushware::tVal m_screenScale;
    static Mushware::U32 m_context;
    static bool m_swapValid;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
