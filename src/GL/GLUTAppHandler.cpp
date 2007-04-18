//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLUTAppHandler.cpp
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
//%Header } a59SgSC+hfPI5E1aJGy/+Q
/*
 * $Id: GLUTAppHandler.cpp,v 1.28 2006/06/01 15:38:55 southa Exp $
 * $Log: GLUTAppHandler.cpp,v $
 * Revision 1.28  2006/06/01 15:38:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.27  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.26  2005/02/03 21:02:51  southa
 * Build fixes
 *
 * Revision 1.25  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.24  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.23  2003/08/21 23:08:32  southa
 * Fixed file headers
 *
 * Revision 1.22  2003/01/20 10:45:24  southa
 * Singleton tidying
 *
 * Revision 1.21  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.20  2003/01/12 17:32:51  southa
 * Mushcore work
 *
 * Revision 1.19  2003/01/09 14:56:59  southa
 * Created Mushcore
 *
 * Revision 1.18  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.17  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.16  2002/12/03 20:28:14  southa
 * Network, player and control work
 *
 * Revision 1.15  2002/11/18 18:55:56  southa
 * Game resume and quit
 *
 * Revision 1.14  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.13  2002/10/15 14:02:29  southa
 * Mode changes
 *
 * Revision 1.12  2002/10/14 18:13:17  southa
 * GLModeDef work
 *
 * Revision 1.11  2002/08/27 08:56:21  southa
 * Source conditioning
 *
 * Revision 1.10  2002/08/17 10:41:50  southa
 * Designer fixes
 *
 * Revision 1.9  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.8  2002/08/02 15:20:54  southa
 * Frame rate timing
 *
 * Revision 1.6  2002/07/19 15:44:40  southa
 * Graphic optimisations
 *
 * Revision 1.5  2002/07/10 16:37:39  southa
 * Cursor removal
 *
 * Revision 1.4  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/23 10:42:33  southa
 * SDL input
 *
 * Revision 1.1  2002/06/21 18:50:16  southa
 * SDLAppHandler added
 *
 */

#include "GLUTAppHandler.h"
#include "GLAppSignal.h"
#include "GLStandard.h"
#include "GLUtils.h"

#include "mushPlatform.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

#if 0

S32 GLUTAppHandler::m_mouseX=0;
S32 GLUTAppHandler::m_mouseY=0;
S32 GLUTAppHandler::m_lastMouseX=0;
S32 GLUTAppHandler::m_lastMouseY=0;
S32 GLUTAppHandler::m_mouseXDelta=0;
S32 GLUTAppHandler::m_mouseYDelta=0;
bool GLUTAppHandler::m_lastMouseValid=false;

GLUTAppHandler::GLUTAppHandler():
    m_visible(true),
    m_keyState(GLKeys::kNumberOfKeys, false),
    m_latchedKeyState(GLKeys::kNumberOfKeys, false)
{}

void
GLUTAppHandler::Initialise(void)
{
}

void
GLUTAppHandler::Idle(void)
{
    MushcoreAppHandler::Idle();
}

void
GLUTAppHandler::Display(void)
{
}

void
GLUTAppHandler::KeyboardSignal(const GLKeyboardSignal& inSignal)
{
    MUSHCOREASSERT(inSignal.keyValue.ValueGet() < m_keyState.size());
    m_keyState[inSignal.keyValue.ValueGet()]=inSignal.keyDown;
    if (inSignal.keyDown)
    {
        m_latchedKeyState[inSignal.keyValue.ValueGet()]=true;
    }
    
    if (inSignal.keyValue.ValueGet() == 27 && inSignal.keyDown)
    {
        // Escape key pressed
        MushcoreAppHandler::Sgl().Signal(MushcoreAppSignal(MushcoreAppSignal::kEscape));
    }
}

bool
GLUTAppHandler::KeyStateGet(const GLKeys& inKey) const
{
    MUSHCOREASSERT(inKey.ValueGet() < m_keyState.size());
    return m_keyState[inKey.ValueGet()];
}


bool
GLUTAppHandler::LatchedKeyStateTake(const GLKeys& inKey)
{
    MUSHCOREASSERT(inKey.ValueGet() < m_keyState.size());
    bool state=m_latchedKeyState[inKey.ValueGet()];
    if (state)
    {
        m_latchedKeyState[inKey.ValueGet()]=false;
    }
    return state;
}

void
GLUTAppHandler::MousePositionGet(tVal& outX, tVal& outY) const
{
    // Needs fixing
    outX=m_mouseX;
    outY=m_mouseY;
}

void
GLUTAppHandler::UnboundedMousePositionGet(S32& outX, S32& outY) const
{
    // Not tested
    outX=m_mouseXDelta;
    outY=m_mouseYDelta; 
}

void
GLUTAppHandler::RegisterHandlers(void)
{
    glutVisibilityFunc(VisibilityHandler);
    glutDisplayFunc(DisplayHandler);
    glutIdleFunc(IdleHandler);
    glutKeyboardFunc(KeyboardHandler);
    glutKeyboardUpFunc(KeyboardUpHandler);
    glutSpecialFunc(SpecialHandler);
    glutSpecialUpFunc(SpecialUpHandler);
    glutPassiveMotionFunc(PassiveMotionHandler);
    glutIgnoreKeyRepeat(1);
}


void
GLUTAppHandler::EnterScreen(const GLModeDef& inDef)
{
    char *argv[] = {"glutInit", ""};
    int argc=sizeof(argv)/sizeof(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE /* | GLUT_ALPHA */);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);

    switch (1)
    {
        case 1:
            m_width=1024;
            m_height=768;
            glutGameModeString("1024x768:32@85");
            glutEnterGameMode();
            break;

        case 2:
            m_width=640;
            m_height=480;
            glutInitWindowSize(m_width,m_height);
            glutCreateWindow("Game");
            break;
            
        default:
            throw(MushcoreLogicFail("Bad value to GLUTAppHandler::EnterScreen"));
    }
    RegisterHandlers();
    GLUtils::CheckGLError();
    m_modeDef = inDef;
}

const GLModeDef&
GLUTAppHandler::CurrentModeDefGet(void)
{
    return m_modeDef;
}

void
GLUTAppHandler::PostRedisplay(void)
{
    glutPostRedisplay();
}

void
GLUTAppHandler::SwapBuffers(void)
{
    glutSwapBuffers();
}

U32
GLUTAppHandler::MillisecondsGet(void) const
{
    return glutGet(GLUT_ELAPSED_TIME);
}

void
GLUTAppHandler::IdleHandler(void)
{
    Sgl().Idle();
}

void
GLUTAppHandler::VisibilityHandler(int inState)
{
    if (inState == GLUT_NOT_VISIBLE)
    {
        Sgl().Signal(GLAppSignal(GLAppSignal::kVisible));
    }
    else if (inState == GLUT_VISIBLE)
    {
        Sgl().Signal(GLAppSignal(GLAppSignal::kVisible));
    }
}

void
GLUTAppHandler::DisplayHandler(void)
{
    Sgl().Signal(GLAppSignal(GLAppSignal::kDisplay));
}

void
GLUTAppHandler::KeyboardHandler(unsigned char inKey, int inX, int inY)
{
    Sgl().Signal(GLKeyboardSignal(1, inKey, inX, inY));
}

void
GLUTAppHandler::KeyboardUpHandler(unsigned char inKey, int inX, int inY)
{
    Sgl().Signal(GLKeyboardSignal(0, inKey, inX, inY));
}

void
GLUTAppHandler::SpecialHandler(int inKey, int inX, int inY)
{
    Sgl().Signal(GLKeyboardSignal(1, TranslateSpecialKey(inKey), inX, inY));
}

void
GLUTAppHandler::SpecialUpHandler(int inKey, int inX, int inY)
{
    Sgl().Signal(GLKeyboardSignal(0, TranslateSpecialKey(inKey), inX, inY));
}

void
GLUTAppHandler::PassiveMotionHandler(int inX, int inY)
{
    // Not tested
    S32 deltaX=0;
    S32 deltaY=0;
    
    if (!m_lastMouseValid)
    {
        m_lastMouseX=inX;
        m_lastMouseY=inY;
    }
    
    if (m_lastMouseValid)
    {
        m_mouseXDelta+=deltaX;
        m_mouseYDelta+=deltaY;
    }
    else
    {
        m_lastMouseValid=true;
    }

    m_mouseX=inX;
    m_mouseY=inY;
}

void
GLUTAppHandler::SetCursorState(bool inValue)
{
    if (inValue)
    {
        glutSetCursor(GLUT_CURSOR_INHERIT);
    }
    else
    {
        glutSetCursor(GLUT_CURSOR_NONE);
    }
    
}

void
GLUTAppHandler::Signal(const MushcoreAppSignal& inSignal)
{
    switch (inSignal.SigNumberGet())
    {
        case GLAppSignal::kDisplay:
            Display();
            break;

        case GLAppSignal::kVisible:
            m_visible=true;
            break;

        case GLAppSignal::kNotVisible:
            m_visible=false;
            break;

        case GLAppSignal::kKeyboard:
        {
            KeyboardSignal(dynamic_cast<const GLKeyboardSignal&>(inSignal));
        }
        break;

        default:
            if (inSignal.IsMushcoreAppSignal())
            {
                MushcoreAppHandler::Signal(inSignal);
            }
            else
            {
                cerr << "Unhandled GLUTAppHandler signal 0x" << hex << inSignal.SigNumberGet() << dec << endl;
            }
            break;
    }
}    

void
GLUTAppHandler::MainLoop(void)
{
    glutMainLoop();
    GLUtils::CheckGLError();
}

void
GLUTAppHandler::PollForControlEvents(void)
{
    // Can't do it
}

void
GLUTAppHandler::AppQuit(void)
{
    exit(0);
}

void
GLUTAppHandler::KeysOfInterestSet(const vector<GLKeys::tKeyValue>& inKeyValues)
{
    MUSHCOREASSERT(false);
}

void
GLUTAppHandler::ReadHistoricControlState(S32& outUnboundedMouseX, S32& outUnboundedMouseY, vector<bool>& outKeys, tVal inMsec)
{
    MUSHCOREASSERT(false);
}

GLKeys
GLUTAppHandler::TranslateSpecialKey(int inKey)
{
    switch (inKey)
    {
        case GLUT_KEY_F1:
            return GLKeys::kKeyF1;

        case GLUT_KEY_F2:
            return GLKeys::kKeyF2;

        case GLUT_KEY_F3:
            return GLKeys::kKeyF3;

        case GLUT_KEY_F4:
            return GLKeys::kKeyF4;

        case GLUT_KEY_F5:
            return GLKeys::kKeyF5;

        case GLUT_KEY_F6:
            return GLKeys::kKeyF6;

        case GLUT_KEY_F7:
            return GLKeys::kKeyF7;

        case GLUT_KEY_F8:
            return GLKeys::kKeyF8;

        case GLUT_KEY_F9:
            return GLKeys::kKeyF9;

        case GLUT_KEY_F10:
            return GLKeys::kKeyF10;

        case GLUT_KEY_F11:
            return GLKeys::kKeyF11;

        case GLUT_KEY_F12:
            return GLKeys::kKeyF12;

        case GLUT_KEY_LEFT:
            return GLKeys::kKeyLeft;

        case GLUT_KEY_UP:
            return GLKeys::kKeyUp;

        case GLUT_KEY_RIGHT:
            return GLKeys::kKeyRight;

        case GLUT_KEY_DOWN:
            return GLKeys::kKeyDown;

        case GLUT_KEY_PAGE_UP:
            return GLKeys::kKeyPageUp;

        case GLUT_KEY_PAGE_DOWN:
            return GLKeys::kKeyPageDown;

        case GLUT_KEY_HOME:
            return GLKeys::kKeyHome;

        case GLUT_KEY_END:
            return GLKeys::kKeyEnd;

        case GLUT_KEY_INSERT:
            return GLKeys::kKeyInsert;

        default:
            cerr << "Unrecognised special key from GLUT " << inKey << endl;
            return 0;
    }
}

#endif

