/*
 * $Id: WrangleCommandHandler.cpp,v 1.2 2002/03/21 22:07:54 southa Exp $
 * $Log: WrangleCommandHandler.cpp,v $
 * Revision 1.2  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 * Revision 1.1  2002/03/18 22:21:12  southa
 * Initial wrangle command
 *
 */

#include "WrangleCommandHandler.hp"
#include "mushCore.hp"
#include "mushGL.hp"

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
