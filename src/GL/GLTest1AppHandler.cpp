//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTest1AppHandler.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ArNN26gY6DQPZ70a6nlDuQ
/*
 * $Id: GLTest1AppHandler.cpp,v 1.30 2003/08/21 23:08:30 southa Exp $
 * $Log: GLTest1AppHandler.cpp,v $
 * Revision 1.30  2003/08/21 23:08:30  southa
 * Fixed file headers
 *
 * Revision 1.29  2003/01/20 12:23:20  southa
 * Code and interface tidying
 *
 * Revision 1.28  2003/01/20 10:45:24  southa
 * Singleton tidying
 *
 * Revision 1.27  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.26  2003/01/11 17:07:51  southa
 * Mushcore library separation
 *
 * Revision 1.25  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.24  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.23  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.22  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.21  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.20  2002/10/14 18:13:17  southa
 * GLModeDef work
 *
 * Revision 1.19  2002/10/12 15:25:03  southa
 * Facet renderer
 *
 * Revision 1.18  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.17  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.16  2002/08/01 16:47:10  southa
 * First multi-box collsion checking
 *
 * Revision 1.15  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.14  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.13  2002/06/20 15:50:29  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.12  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.11  2002/05/28 16:37:39  southa
 * Texture references and decomposer
 *
 * Revision 1.10  2002/05/28 13:07:00  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.9  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 * Revision 1.8  2002/05/10 16:41:43  southa
 * Changed .hp files to .h
 *
 * Revision 1.7  2002/05/08 16:31:21  southa
 * Created API directory
 *
 * Revision 1.6  2002/03/18 22:22:15  southa
 * Initial wrangle command
 *
 * Revision 1.5  2002/03/07 22:24:34  southa
 * Command interpreter working
 *
 * Revision 1.4  2002/02/26 17:01:38  southa
 * Completed Sprite loader
 *
 * Revision 1.3  2002/02/24 22:49:33  southa
 * Got working under cygwin
 *
 * Revision 1.2  2002/02/23 20:05:15  southa
 * Added libraries and test files
 *
 * Revision 1.1  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 */

#include "GLTest1AppHandler.h"

#include "Mushcore.h"
#include "mushGL.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller
GLTest1CommandHandlerInstaller(GLTest1AppHandler::Install);

void
GLTest1AppHandler::Initialise(void)
{
    EnterScreen(GLModeDef::Default());
    GLUtils::CheckGLError();
}

void
GLTest1AppHandler::Display(void)
{
    static double ticker=0;
    ticker+=0.01;
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::OrthoPrologue();

    GLLine line1(GLPoint(-50,-100), GLPoint(-50,100));
    GLLine line3(GLPoint(-100,50), GLPoint(100,50));
    GLRectangle rect1(-100,-100,-30,-50);
    GLLine line2(GLPoint(-30,-100), GLPoint(170,100));
    line2.RotateAboutCentre(ticker);
    if (line1.IsIntersecting(line2))
    {
        GLState::ColourSet(0,1,0);
    }
    else
    {
        GLState::ColourSet(0.5,0.5,0.5);
    }
    glTranslatef(200,200,0);
    GLState::ColourSet(0.5,0.5,0.5);
    line2.Render();
    if (line1.IsIntersecting(line2))
    {
GLState::ColourSet(0,1,0);
    }
    else
    {
GLState::ColourSet(0.5,0.5,0.5);
    }    
    line1.Render();
#if 1
    if (line3.IsIntersecting(line2))
    {
GLState::ColourSet(0,1,0);
    }
    else
    {
GLState::ColourSet(0.5,0.5,0.5);
    }
    line3.Render();
#endif
#if 1
    if (rect1.IsIntersecting(line2))
    {
GLState::ColourSet(0,1,0);
    }
    else
    {
GLState::ColourSet(0.5,0.5,0.5);
    }
    rect1.Render();
#endif
GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
}

void
GLTest1AppHandler::Idle(void)
{
    GLUtils::PostRedisplay();
}

MushcoreScalar
GLTest1AppHandler::GLTest1(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreAppHandler::Sgl().Mutate(new GLTest1AppHandler);
    return MushcoreScalar(0);
}

void
GLTest1AppHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("gltest1", GLTest1);
}
