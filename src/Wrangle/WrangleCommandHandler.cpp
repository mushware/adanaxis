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
 * $Id: WrangleCommandHandler.cpp,v 1.10 2002/12/29 21:00:01 southa Exp $
 * $Log: WrangleCommandHandler.cpp,v $
 * Revision 1.10  2002/12/29 21:00:01  southa
 * More build fixes
 *
 * Revision 1.9  2002/12/20 13:17:49  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:42:08  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 08:56:30  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:52  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:20  southa
 * More designer work
 *
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

using namespace Mushware;
using namespace std;

MushcoreInstaller WrangleCommandHandlerInstaller(WrangleCommandHandler::Install);

MushcoreScalar
WrangleCommandHandler::Wrangle(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    string filename;
    filename=ioCommand.PopString();
    string loadCommand("loadpixmap 0 ");
    loadCommand.append(filename);
    loadCommand.append(";");
    MushcoreApp::Instance().Process(loadCommand);

    GLTextureRef texRef("0");
    GLTexture& tex=*texRef.TextureGet();

    cout << "# Wrangling image " << filename << endl;
    cout << "# " << tex << endl;

    MushcoreAppHandler::Instance().Mutate(new GLWrangleAppHandler);

    return MushcoreScalar(0);
}

void
WrangleCommandHandler::Install(void)
{
    MushcoreApp::Instance().AddHandler("wrangle", Wrangle);
}
