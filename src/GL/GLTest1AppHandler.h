#ifndef GLTEST1APPHANDLER_H
#define GLTEST1APPHANDLER_H
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
 * $Id: GLTest1AppHandler.h,v 1.3 2002/06/20 15:50:29 southa Exp $
 * $Log: GLTest1AppHandler.h,v $
 * Revision 1.3  2002/06/20 15:50:29  southa
 * Subclassed GLAppHandler
 *
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
#endif
