/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GLUTAppHandler.cpp,v 1.13 2002/10/15 14:02:29 southa Exp $
 * $Log: GLUTAppHandler.cpp,v $
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
#include "GLStandard.h"
#include "GLUtils.h"
#include "GLAppSignal.h"

#include "mushPlatform.h"

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
    CoreAppHandler::Idle();
}

void
GLUTAppHandler::Display(void)
{
}

void
GLUTAppHandler::KeyboardSignal(const GLKeyboardSignal& inSignal)
{
    COREASSERT(inSignal.keyValue.ValueGet() < m_keyState.size());
    m_keyState[inSignal.keyValue.ValueGet()]=inSignal.keyDown;
    if (inSignal.keyDown)
    {
        m_latchedKeyState[inSignal.keyValue.ValueGet()]=true;
    }
    
    if (inSignal.keyValue.ValueGet() == 27 && inSignal.keyDown)
    {
        // Escape key pressed
        CoreAppHandler::Instance().Signal(CoreAppSignal(CoreAppSignal::kEscape));
    }
}

bool
GLUTAppHandler::KeyStateGet(const GLKeys& inKey) const
{
    COREASSERT(inKey.ValueGet() < m_keyState.size());
    return m_keyState[inKey.ValueGet()];
}


bool
GLUTAppHandler::LatchedKeyStateTake(const GLKeys& inKey)
{
    COREASSERT(inKey.ValueGet() < m_keyState.size());
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
GLUTAppHandler::MouseDeltaTake(tVal& outXDelta, tVal& outYDelta)
{
    outXDelta=m_mouseXDelta/m_width;
    outYDelta=m_mouseYDelta/m_width; 
    m_mouseXDelta=0;
    m_mouseYDelta=0;
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
            throw(LogicFail("Bad value to GLUTAppHandler::EnterScreen"));
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
    Instance().Idle();
}

void
GLUTAppHandler::VisibilityHandler(int inState)
{
    if (inState == GLUT_NOT_VISIBLE)
    {
        Instance().Signal(GLAppSignal(GLAppSignal::kVisible));
    }
    else if (inState == GLUT_VISIBLE)
    {
        Instance().Signal(GLAppSignal(GLAppSignal::kVisible));
    }
}

void
GLUTAppHandler::DisplayHandler(void)
{
    Instance().Signal(GLAppSignal(GLAppSignal::kDisplay));
}

void
GLUTAppHandler::KeyboardHandler(unsigned char inKey, int inX, int inY)
{
    Instance().Signal(GLKeyboardSignal(1, inKey, inX, inY));
}

void
GLUTAppHandler::KeyboardUpHandler(unsigned char inKey, int inX, int inY)
{
    Instance().Signal(GLKeyboardSignal(0, inKey, inX, inY));
}

void
GLUTAppHandler::SpecialHandler(int inKey, int inX, int inY)
{
    Instance().Signal(GLKeyboardSignal(1, TranslateSpecialKey(inKey), inX, inY));
}

void
GLUTAppHandler::SpecialUpHandler(int inKey, int inX, int inY)
{
    Instance().Signal(GLKeyboardSignal(0, TranslateSpecialKey(inKey), inX, inY));
}

void
GLUTAppHandler::PassiveMotionHandler(int inX, int inY)
{
    S32 deltaX=0;
    S32 deltaY=0;
    
    if (!m_lastMouseValid)
    {
        m_lastMouseX=inX;
        m_lastMouseY=inY;
    }
    
    if (PlatformInputUtils::MouseDeltaPrologue(inX, inY, m_lastMouseX, m_lastMouseY))
    {
    	PlatformInputUtils::GetMouseDeltas(deltaX, deltaY, inX, inY, m_lastMouseX, m_lastMouseY);
    	PlatformInputUtils::MouseDeltaEpilogue(inX, inY, m_lastMouseX, m_lastMouseY);
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
GLUTAppHandler::Signal(const CoreAppSignal& inSignal)
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
            if (inSignal.IsCoreAppSignal())
            {
                CoreAppHandler::Signal(inSignal);
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
