/*
 * $Id: GLCommandHandler.cpp,v 1.11 2002/05/10 16:41:42 southa Exp $
 * $Log: GLCommandHandler.cpp,v $
 * Revision 1.11  2002/05/10 16:41:42  southa
 * Changed .hp files to .h
 *
 * Revision 1.10  2002/05/08 16:31:20  southa
 * Created API directory
 *
 * Revision 1.9  2002/03/18 22:22:15  southa
 * Initial wrangle command
 *
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

#include "GLCommandHandler.h"
#include "mushCore.h"
#include "GLAppHandler.h"
#include "GLData.h"
#include "GLTextureSpr.h"
#include "GLTextureGIF.h"
#include "GLTextureTIFF.h"
#include "GLTest.h"

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
    string name;
    string filename;
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: loadpixmap <name> <filename>"));
    }
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    CoreRegExp re;
    if (re.Search(filename, "(spr|SPR)$"))
    {
        GLData::Instance().AddTexture(GLTextureSpr(filename));
    }
    else if (re.Search(filename, "(gif|GIF)$"))
    {
        GLData::Instance().AddTexture(GLTextureGIF(filename));
    }
    else if (re.Search(filename, "(tif|tiff|TIF|TIFF)$"))
    {
        GLData::Instance().AddTexture(GLTextureTIFF(filename));
    }
    else
    {
        throw(LoaderFail(filename, "Couldn't decode extension"));
    }

    return CoreScalar(0);
}

CoreScalar
GLCommandHandler::Decompose(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    // Format of command is decompose <pixmapname> <xsize> <ysize> <xstart> <ystart> <xnum> <ynum>
}


void
GLCommandHandler::Install(void)
{
    CoreApp::Instance().AddHandler("initgl", InitGL);
    CoreApp::Instance().AddHandler("loadpixmap", LoadPixmap);
    CoreApp::Instance().AddHandler("decompose", Decompose);
}
