/*
 * $Id: WrangleCommandHandler.cpp,v 1.1 2002/03/18 22:21:12 southa Exp $
 * $Log: WrangleCommandHandler.cpp,v $
 * Revision 1.1  2002/03/18 22:21:12  southa
 * Initial wrangle command
 *
 */

#include "WrangleCommandHandler.hp"
#include "CoreApp.hp"
#include "CoreAppHandler.hp"
#include "CoreInstaller.hp"
#include "GL/GLData.hp"
#include "GL/GLTexture.hp"

#include "GLWrangleAppHandler.hp"

CoreInstaller WrangleCommandHandlerInstaller(WrangleCommandHandler::Install);

CoreScalar
WrangleCommandHandler::Wrangle(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    string filename;
    filename=ioCommand.PopString();
    string loadCommand("loadpixmap ");
    loadCommand.append(filename);
    loadCommand.append(";");
    CoreApp::Instance().Process(loadCommand);

    const GLTexture& tex=GLData::Instance().GetTexture(0);

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
