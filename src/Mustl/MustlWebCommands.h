//%includeGuardStart {
#ifndef MUSTLWEBCOMMANDS_H
#define MUSTLWEBCOMMANDS_H
//%includeGuardStart } 8zTsToM8Bq6hufrlWy88rg
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlWebCommands.h
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
//%Header } DbuAl3X/X/fxunXwfTlU2g
/*
 * $Id: MustlWebCommands.h,v 1.10 2006/06/01 15:39:55 southa Exp $
 * $Log: MustlWebCommands.h,v $
 * Revision 1.10  2006/06/01 15:39:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/05/19 13:02:20  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:32  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/05/21 19:01:41  southa
 * Prerelease tweaks
 *
 * Revision 1.4  2003/04/06 12:35:23  southa
 * Fixes for release
 *
 * Revision 1.3  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.2  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.1  2003/01/14 17:38:22  southa
 * Mustl web configuration
 *
 */

#include "MustlStandard.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

class MustlWebCommands
{
public:
    static MushcoreScalar MustlPostValues(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlInputWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlServerStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlLinkStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlPrintPackageID(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlPrintMetaPackageID(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlPrintApplicationName(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void NullFunction(void);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
