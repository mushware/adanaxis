#ifndef GLTEST1APPHANDLER_H
#define GLTEST1APPHANDLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLTest1AppHandler.h,v 1.11 2003/01/09 14:56:58 southa Exp $
 * $Log: GLTest1AppHandler.h,v $
 * Revision 1.11  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.10  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.6  2002/08/01 16:47:10  southa
 * First multi-box collsion checking
 *
 * Revision 1.5  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:05  southa
 * Build process fixes
 *
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
#include "SDLAppHandler.h"
#include "Mushcore.h"

class GLTest1AppHandler : public SDLAppHandler
{
public:
    virtual void Initialise(void);
    virtual void Display(void);
    virtual void Idle(void);
    static MushcoreScalar GLTest1(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

protected:
private:
};
#endif
