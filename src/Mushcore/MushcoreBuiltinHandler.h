//%includeGuardStart {
#ifndef MUSHCOREBUILTINHANDLER_H
#define MUSHCOREBUILTINHANDLER_H
//%includeGuardStart } NJwyAG3KnC5juZ5dhz2MZw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreBuiltinHandler.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } vPhcKwt2ovWE9e0BRD4CeA
/*
 * $Id: MushcoreBuiltinHandler.h,v 1.6 2003/08/21 23:09:06 southa Exp $
 * $Log: MushcoreBuiltinHandler.h,v $
 * Revision 1.6  2003/08/21 23:09:06  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.4  2003/01/13 14:32:02  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.3  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.6  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.2  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 09:10:06  southa
 * Name changed to MushcoreBuiltinHandler
 *
 * Revision 1.2  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/03/07 22:24:32  southa
 * Command interpreter working
 *
 */

#include "MushcoreCommandHandler.h"
#include "MushcoreStandard.h"

class MushcoreBuiltinHandler
{
public:
    static MushcoreScalar Load(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static MushcoreScalar ConfigSet(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static void Install(void);
    static void NullFunction(void);
protected:

private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
