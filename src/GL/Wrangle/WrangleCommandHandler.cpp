/*
 * $Id$
 * $Log$
 */

#include "WrangleCommandHandler.hp"
#include "CoreApp.hp"
#include "CoreInstaller.hp"
#include "GL/GLData.hp"
#include "GL/GLTexture.hp"

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

    cout << "# Wrangling texture " << filename << endl;
    cout << "# " << tex << endl;

    return CoreScalar(0);
}

void
WrangleCommandHandler::Install(void)
{
    CoreApp::Instance().AddHandler("wrangle", Wrangle);
}
