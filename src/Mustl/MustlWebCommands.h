#ifndef MUSTLWEBCOMMANDS_H
#define MUSTLWEBCOMMANDS_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MustlWebCommands.h,v 1.5 2003/05/21 19:01:41 southa Exp $
 * $Log: MustlWebCommands.h,v $
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
#endif
