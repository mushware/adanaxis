/*
 * $Id: GLCommandHandler.h,v 1.1 2002/05/10 16:41:43 southa Exp $
 * $Log: GLCommandHandler.h,v $
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
};
