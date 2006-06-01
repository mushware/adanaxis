//%includeGuardStart {
#ifndef GLCOMMANDHANDLER_H
#define GLCOMMANDHANDLER_H
//%includeGuardStart } gJO88MJSAt/MwJK6xZTl0g
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLCommandHandler.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 0nKUZAH7+qFfQa0NavanlQ
/*
 * $Id: GLCommandHandler.h,v 1.17 2005/05/19 13:01:58 southa Exp $
 * $Log: GLCommandHandler.h,v $
 * Revision 1.17  2005/05/19 13:01:58  southa
 * Mac release work
 *
 * Revision 1.16  2004/09/27 22:42:08  southa
 * MSVC compilation fixes
 *
 * Revision 1.15  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.14  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.13  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:19  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.10  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:42:00  southa
 * Source conditioning
 *
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

#include "mushMushcore.h"

class GLCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar LoadPixmap(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar Decompose(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar DumpTextures(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
