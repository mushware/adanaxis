//%includeGuardStart {
#ifndef GLTEST1APPHANDLER_H
#define GLTEST1APPHANDLER_H
//%includeGuardStart } DKT2IUhI+XKwSGb0EYdFww
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTest1AppHandler.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } 60XHbM/laAQp3Zj8zafhfw
/*
 * $Id: GLTest1AppHandler.h,v 1.17 2004/01/06 20:46:49 southa Exp $
 * $Log: GLTest1AppHandler.h,v $
 * Revision 1.17  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.16  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.15  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.14  2003/08/21 23:08:30  southa
 * Fixed file headers
 *
 * Revision 1.13  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.12  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
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
#include "mushMushcore.h"
#include "SDLAppHandler.h"

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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
