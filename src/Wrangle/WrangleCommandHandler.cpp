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
 * $Id: WrangleCommandHandler.cpp,v 1.4 2002/06/27 12:36:09 southa Exp $
 * $Log: WrangleCommandHandler.cpp,v $
 * Revision 1.4  2002/06/27 12:36:09  southa
 * Build process fixes
 *
 * Revision 1.3  2002/05/28 16:37:36  southa
 * Texture references and decomposer
 *
 * Revision 1.2  2002/05/10 16:40:39  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/09 17:08:08  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.3  2002/05/08 16:31:20  southa
 * Created API directory
 *
 * Revision 1.2  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 * Revision 1.1  2002/03/18 22:21:12  southa
 * Initial wrangle command
 *
 */

#include "WrangleCommandHandler.h"
#include "mushCore.h"
#include "mushGL.h"

#include "GLWrangleAppHandler.h"

CoreInstaller WrangleCommandHandlerInstaller(WrangleCommandHandler::Install);

CoreScalar
WrangleCommandHandler::Wrangle(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    string filename;
    filename=ioCommand.PopString();
    string loadCommand("loadpixmap 0 ");
    loadCommand.append(filename);
    loadCommand.append(";");
    CoreApp::Instance().Process(loadCommand);

    GLTextureRef texRef("0");
    GLTexture& tex=*texRef.TextureGet();

    cout << "# Wrangling image " << filename << endl;
    cout << "# " << tex << endl;

    CoreAppHandler::Instance().Mutate(new GLWrangleAppHandler);

    return CoreScalar(0);
}

void
WrangleCommandHandler::Install(void)
{
    CoreApp::Instance().AddHandler("wrangle", Wrangle);
}
