/*
 * $Id: GLAppHandler.cpp,v 1.7 2002/05/24 18:10:43 southa Exp $
 * $Log: GLAppHandler.cpp,v $
 * Revision 1.7  2002/05/24 18:10:43  southa
 * CoreXML and game map
 *
 * Revision 1.6  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 * Revision 1.5  2002/05/10 16:41:42  southa
 * Changed .hp files to .h
 *
 * Revision 1.4  2002/05/08 16:31:20  southa
 * Created API directory
 *
 * Revision 1.3  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 * Revision 1.2  2002/02/24 22:49:33  southa
 * Got working under cygwin
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "GLAppHandler.h"
#include "GLStandard.h"
#include "GLUtils.h"
#include "GLAppSignal.h"

void
GLAppHandler::Initialise(void)
{
    GLUtils::StandardInit();
    glutCreateWindow("GLApp");
    RegisterHandlers();
}

void
GLAppHandler::Idle(void)
{
    CoreAppHandler::Idle();
}

void
GLAppHandler::Display(void)
{
}

void
GLAppHandler::KeyboardSignal(const GLKeyboardSignal& inSignal)
{
    COREASSERT(inSignal.keyValue.ValueGet() < m_keyState.size());
    m_keyState[inSignal.keyValue.ValueGet()]=inSignal.keyDown;

    if (inSignal.keyValue.ValueGet() == 27 && inSignal.keyDown)
    {
        // Escape key pressed
        CoreAppHandler::Instance().Signal(CoreAppSignal(CoreAppSignal::kEscape));
    }
}

bool
GLAppHandler::KeyStateGet(const GLKeys& inKey) const
{
    COREASSERT(inKey.ValueGet() < m_keyState.size());
    return m_keyState[inKey.ValueGet()];
}

void
GLAppHandler::RegisterHandlers(void)
{
    glutVisibilityFunc(VisibilityHandler);
    glutDisplayFunc(DisplayHandler);
    glutIdleFunc(IdleHandler);
    glutKeyboardFunc(KeyboardHandler);
    glutKeyboardUpFunc(KeyboardUpHandler);
    glutSpecialFunc(SpecialHandler);
    glutSpecialUpFunc(SpecialUpHandler);
    glutIgnoreKeyRepeat(1);
}

void
GLAppHandler::IdleHandler(void)
{
    Instance().Idle();
}

void
GLAppHandler::VisibilityHandler(int inState)
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
GLAppHandler::DisplayHandler(void)
{
    Instance().Signal(GLAppSignal(GLAppSignal::kDisplay));
}

void
GLAppHandler::KeyboardHandler(unsigned char inKey, int inX, int inY)
{
    Instance().Signal(GLKeyboardSignal(1, inKey, inX, inY));
}

void
GLAppHandler::KeyboardUpHandler(unsigned char inKey, int inX, int inY)
{
    Instance().Signal(GLKeyboardSignal(0, inKey, inX, inY));
}

void
GLAppHandler::SpecialHandler(int inKey, int inX, int inY)
{
    Instance().Signal(GLKeyboardSignal(1, TranslateSpecialKey(inKey), inX, inY));
}

void
GLAppHandler::SpecialUpHandler(int inKey, int inX, int inY)
{
    Instance().Signal(GLKeyboardSignal(0, TranslateSpecialKey(inKey), inX, inY));
}

void
GLAppHandler::Signal(const CoreAppSignal& inSignal)
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
                cerr << "Unhandled GLAppHandler signal 0x" << hex << inSignal.SigNumberGet() << dec << endl;
            }
            break;
    }
}    

void
GLAppHandler::MainLoop(void)
{
    glutMainLoop();
    GLUtils::CheckGLError();
}

GLKeys
GLAppHandler::TranslateSpecialKey(int inKey)
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