/*
 * $Id: GLCommandHandler.cpp,v 1.8 2002/03/07 22:24:34 southa Exp $
 * $Log: GLCommandHandler.cpp,v $
 * Revision 1.8  2002/03/07 22:24:34  southa
 * Command interpreter working
 *
 * Revision 1.7  2002/02/26 17:01:38  southa
 * Completed Sprite loader
 *
 * Revision 1.6  2002/02/25 23:05:14  southa
 * Subclassed GLTexture
 *
 * Revision 1.5  2002/02/23 20:05:15  southa
 * Added libraries and test files
 *
 * Revision 1.4  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.3  2002/02/18 22:43:53  southa
 * First stage GIF loader
 *
 * Revision 1.2  2002/02/18 22:04:37  southa
 * Initial texture loading
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "GLCommandHandler.hp"
#include "CoreApp.hp"
#include "CoreTest.hp"
#include "CoreInstaller.hp"
#include "CoreRegExp.hp"
#include "GLAppHandler.hp"
#include "GLData.hp"
#include "GLTextureSpr.hp"
#include "GLTextureGIF.hp"
#include "GLTest.hp"

CoreInstaller GLCommandHandlerInstaller(GLCommandHandler::Install);

CoreScalar
GLCommandHandler::InitGL(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    // Save inStr to context
    CoreAppHandler::Instance().Mutate(new GLAppHandler);
    return CoreScalar(0);
}

CoreScalar
GLCommandHandler::LoadPixmap(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    string filename;
    ioCommand.PopParam(filename);
    try
    {
        CoreRegExp re;
        if (re.Search(filename, "spr$"))
        {
            GLData::Instance().AddTexture(GLTextureSpr(filename));
        }
        else if (re.Search(filename, "gif$"))
        {
            GLData::Instance().AddTexture(GLTextureGIF(filename));
        }
        else
        {
            throw(LoaderFail(filename, "Couldn't decode extension"));
        }
    }
    catch (LoaderFail f)
    {
        cerr << f;
    }
    return CoreScalar(0);
}

void
GLCommandHandler::Install(void)
{
    CoreApp::Instance().AddHandler("initgl", InitGL);
    CoreApp::Instance().AddHandler("loadpixmap", LoadPixmap);
}
