/*
 * $Id: GLAppHandler.h,v 1.5 2002/05/08 16:31:20 southa Exp $
 * $Log: GLAppHandler.h,v $
 * Revision 1.5  2002/05/08 16:31:20  southa
 * Created API directory
 *
 * Revision 1.4  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 * Revision 1.3  2002/02/24 22:49:33  southa
 * Got working under cygwin
 *
 * Revision 1.2  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "mushCore.h"

class GLAppHandler : public CoreAppHandler
{
public:
    GLAppHandler(): m_visible(true) {}
    virtual ~GLAppHandler() {}
    virtual void Initialise(void);
    virtual void Idle(bool& outQuit, int& outUSleepFor);    
    virtual void MainLoop(void);
    virtual void Display(void);
    virtual void Signal(U32 inSignal);

protected:
    void CheckGLError(void);
    void StandardInit(void);
    void OrthoPrologue(void);
    void OrthoEpilogue(void);
    bool IsVisible(void) {return m_visible;}
private:
    enum
    {
        kSignalVisible,
        kSignalNotVisible
    };
    static void IdleHandler(void);
    static void DisplayHandler(void) {Instance().Display();}
    static void VisibilityHandler(int inState);

    bool m_visible;
};
