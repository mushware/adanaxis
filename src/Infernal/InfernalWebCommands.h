//%includeGuardStart {
#ifndef INFERNALWEBCOMMANDS_H
#define INFERNALWEBCOMMANDS_H
//%includeGuardStart } p++98KVnuMYtNKu3WzvMiQ
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalWebCommands.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } spuMRcNqwlu8gDb7Gbt0+g
/*
 * $Id: InfernalWebCommands.h,v 1.5 2006/06/01 15:39:10 southa Exp $
 * $Log: InfernalWebCommands.h,v $
 * Revision 1.5  2006/06/01 15:39:10  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/04 12:23:07  southa
 * File renaming
 *
 * Revision 1.9  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:59  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/17 13:30:39  southa
 * Source conditioning and build fixes
 *
 * Revision 1.6  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
 * Revision 1.5  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.4  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.2  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.1  2002/11/18 13:40:32  southa
 * Moved to correct place
 *
 * Revision 1.5  2002/11/14 19:35:30  southa
 * Configuration work
 *
 * Revision 1.4  2002/11/14 17:29:07  southa
 * Config database
 *
 * Revision 1.3  2002/11/14 11:40:28  southa
 * Configuration handling
 *
 * Revision 1.2  2002/11/12 18:02:13  southa
 * POST handling and handlepostvalues command
 *
 * Revision 1.1  2002/11/07 11:59:02  southa
 * Web commands
 *
 */

#include "mushMushcore.h"

class InfernalWebCommands
{
public:
    static void Install(void);
    static MushcoreScalar PostHandler(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar DisplayModesWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameConfigInputWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameServerStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameClientStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameLinkStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);

private:

};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
