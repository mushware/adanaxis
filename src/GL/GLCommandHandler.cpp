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
 * $Id: GLCommandHandler.cpp,v 1.22 2002/12/29 20:59:52 southa Exp $
 * $Log: GLCommandHandler.cpp,v $
 * Revision 1.22  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.21  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.20  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.19  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.18  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.17  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 * Revision 1.16  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.15  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.14  2002/06/20 15:50:29  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.13  2002/05/28 16:37:39  southa
 * Texture references and decomposer
 *
 * Revision 1.12  2002/05/28 13:07:00  southa
 * Command parser extensions and TIFF loader
 *
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
#include "GLData.h"
#include "GLTest.h"
#include "GLTextureClip.h"
#include "GLTextureGIF.h"
#include "GLTextureRef.h"
#include "GLTextureSpr.h"
#include "GLTextureTIFF.h"
#include "GLUTAppHandler.h"
#include "mushCore.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller GLCommandHandlerInstaller(GLCommandHandler::Install);

MushcoreScalar
GLCommandHandler::InitGL(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    // Save inStr to context
    MushcoreAppHandler::Instance().Mutate(new GLUTAppHandler);
    return MushcoreScalar(0);
}

MushcoreScalar
GLCommandHandler::LoadPixmap(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    string name;
    string filename;
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: loadpixmap <name> <filename>"));
    }
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    MushcoreRegExp re;
    if (re.Search(filename, "(spr|SPR)$"))
    {
        GLData::Instance().TextureAdd(name, GLTextureSpr(filename));
    }
    else if (re.Search(filename, "(gif|GIF)$"))
    {
        GLData::Instance().TextureAdd(name, GLTextureGIF(filename));
    }
    else if (re.Search(filename, "(tif|tiff|TIF|TIFF)$"))
    {
        GLData::Instance().TextureAdd(name, GLTextureTIFF(filename));
    }
    else
    {
        throw(LoaderFail(filename, "Couldn't decode extension"));
    }

    return MushcoreScalar(0);
}

MushcoreScalar
GLCommandHandler::Decompose(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() < 4)
    {
        throw(CommandFail("Usage: decompose <src> <dest>[@] [<xsize> <ysize> [<xstart> <ystart> [<xnum> <ynum>]]]"));
    }
    string srcName, destName;
    ioCommand.PopParam(srcName);
    GLTextureRef srcTexRef(srcName);
    if (!srcTexRef.Exists())
    {
        throw(CommandFail("Pixel map '"+srcName+"' could not be found"));
    }
    ioCommand.PopParam(destName);    

    GLTexture& srcTex=*srcTexRef.TextureGet();
    U32 width=srcTex.Width();
    U32 height=srcTex.Height();
    U32 xsize=width;
    U32 ysize=height;
    U32 xstart=0;
    U32 ystart=0;
    ioCommand.PopParam(xsize);
    ioCommand.PopParam(ysize);
    ioCommand.PopParam(xstart);
    ioCommand.PopParam(ystart);    

    if (xsize == 0 || ysize == 0)
    {
        throw(CommandFail("xsize and ysize must be non-zero"));
    }
    if (xstart >= width || ystart >= height)
    {
        throw(CommandFail("xstart and ystart must be within the texture"));
    }
    U32 xnum=(width-xstart)/xsize;
    U32 ynum=(height-ystart)/ysize;

    ioCommand.PopParam(xnum);
    ioCommand.PopParam(ynum);    

    for (U32 xctr=0; xctr<xnum; ++xctr)
    {
        for (U32 yctr=0; yctr<ynum; ++yctr)
        {
            ostringstream postFix;
            postFix << xctr << "_" << yctr;
            string name(destName);
            name.replace(name.find("@"), 1, postFix.str());
            U32 xbase=xstart+xctr*xsize;
            U32 ybase=ystart+yctr*ysize;
            
            GLData::Instance().TextureAdd(name, GLTextureClip(srcTex, xbase, ybase, xbase+xsize, ybase+ysize));
        }
    }
    return MushcoreScalar(0);
}

MushcoreScalar
GLCommandHandler::DumpTextures(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    GLData::Instance().DumpTextures(cout);
    return MushcoreScalar(0);
}

void
GLCommandHandler::Install(void)
{
    MushcoreApp::Instance().AddHandler("initgl", InitGL);
    MushcoreApp::Instance().AddHandler("loadpixmap", LoadPixmap);
    MushcoreApp::Instance().AddHandler("decompose", Decompose);
    MushcoreApp::Instance().AddHandler("dumptextures", DumpTextures);
}
