//%includeGuardStart {
#ifndef MUSHCORESWITCHES_H
#define MUSHCORESWITCHES_H
//%includeGuardStart } v3JnZAZLBfvo2b5JKlTy4w
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreSwitches.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } S/Td6HO0trjRC2GM5ahWHA
/*
 * $Id: MushcoreSwitches.h,v 1.7 2003/09/17 19:40:36 southa Exp $
 * $Log: MushcoreSwitches.h,v $
 * Revision 1.7  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:18  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.4  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 * Revision 1.3  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/03/18 22:21:12  southa
 * Initial wrangle command
 *
 * Revision 1.1  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 */

#include "MushcoreStandard.h"

#ifdef MUSHCORE_MONKEYTESTING
#define MUSHCORE_IFMONKEYTESTING(a) a
#else
#define MUSHCORE_IFMONKEYTESTING(a)
#endif

#ifdef MUSHCORE_FLEXTESTING
#define MUSHCORE_IFFLEXTESTING(a) a
#else
#define MUSHCORE_IFFLEXTESTING(a)
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
