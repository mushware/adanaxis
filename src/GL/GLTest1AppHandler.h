/*
 * $Id: GLTest1AppHandler.h,v 1.2 2002/05/31 15:18:16 southa Exp $
 * $Log: GLTest1AppHandler.h,v $
 * Revision 1.2  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.1  2002/05/10 16:40:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/05/08 16:31:21  southa
 * Created API directory
 *
 * Revision 1.2  2002/03/07 22:24:34  southa
 * Command interpreter working
 *
 * Revision 1.1  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 */

#include "GLUTAppHandler.h"
#include "mushCore.h"

class GLTest1AppHandler : public GLUTAppHandler
{
public:
    virtual void Initialise(void);
    virtual void Display(void);
    static CoreScalar GLTest1(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static void Install(void);

protected:
private:
};
