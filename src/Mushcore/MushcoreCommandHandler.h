#ifndef MUSHCORECOMMANDHANDLER_H
#define MUSHCORECOMMANDHANDLER_H
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
 * $Id: MushcoreCommandHandler.h,v 1.3 2003/01/11 17:07:53 southa Exp $
 * $Log: MushcoreCommandHandler.h,v $
 * Revision 1.3  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:03  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/03/07 22:24:32  southa
 * Command interpreter working
 *
 * Revision 1.1  2002/03/05 22:44:45  southa
 * Changes to command handling
 *
 * Revision 1.2  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "MushcoreStandard.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

typedef 
MushcoreScalar (*MushcoreCommandHandler)(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
#endif
