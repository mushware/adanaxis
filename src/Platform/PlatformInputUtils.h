//%includeGuardStart {
#ifndef PLATFORMINPUTUTILS_H
#define PLATFORMINPUTUTILS_H
//%includeGuardStart } Xtv80/F44sw65b2ia1nkQg
//%Header {
/*****************************************************************************
 *
 * File: src/Platform/PlatformInputUtils.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Gp4cWtpt1YXvkd2iniZVUA
/*
 * $Id: PlatformInputUtils.h,v 1.14 2004/01/02 21:13:16 southa Exp $
 * $Log: PlatformInputUtils.h,v $
 * Revision 1.14  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.13  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:09:33  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/01/11 13:03:18  southa
 * Use Mushcore header
 *
 * Revision 1.10  2002/12/20 13:17:47  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
 * Revision 1.8  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 * Revision 1.6  2002/10/06 22:09:59  southa
 * Initial lighting test
 *
 * Revision 1.5.4.1  2002/09/04 10:18:04  southa
 * Fixed for MacOS X 10.2
 *
 * Revision 1.5  2002/08/27 08:56:29  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.1  2002/06/06 14:59:57  southa
 * Mouse fixes
 *
 * Revision 1.1  2002/06/06 12:32:37  southa
 * Added support for src/Support/platform
 *
 * Revision 1.1  2002/06/06 10:40:20  southa
 * Created
 *
 */

#include "mushMushcore.h"

class PlatformInputUtils
{
public:
    static void MouseDeltaOverrideGet(Mushware::S32& ioXDelta, Mushware::S32& ioYDelta);
};


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
