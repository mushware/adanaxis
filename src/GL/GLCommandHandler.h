#ifndef GLCOMMANDHANDLER_H
#define GLCOMMANDHANDLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GLCommandHandler.h,v 1.7 2002/08/27 08:56:19 southa Exp $
 * $Log: GLCommandHandler.h,v $
 * Revision 1.7  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 * Revision 1.4  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/28 13:07:00  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.1  2002/05/10 16:41:43  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/05/08 16:31:21  southa
 * Created API directory
 *
 * Revision 1.2  2002/03/07 22:24:34  southa
 * Command interpreter working
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "mushCore.h"

class GLCommandHandler
{
public:
    static void Install(void);
    static CoreScalar InitGL(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar LoadPixmap(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar Decompose(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar DumpTextures(CoreCommand& ioCommand, CoreEnv& ioEnv);
};
#endif
