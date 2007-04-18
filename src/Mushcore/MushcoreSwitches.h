//%includeGuardStart {
#ifndef MUSHCORESWITCHES_H
#define MUSHCORESWITCHES_H
//%includeGuardStart } v3JnZAZLBfvo2b5JKlTy4w
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreSwitches.h
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
//%Header } aP00/MY1pdxGJW7QBlEgXA
/*
 * $Id: MushcoreSwitches.h,v 1.12 2006/06/01 15:39:48 southa Exp $
 * $Log: MushcoreSwitches.h,v $
 * Revision 1.12  2006/06/01 15:39:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/08/02 17:11:28  southa
 * win32 build fixes
 *
 * Revision 1.10  2005/08/01 17:58:12  southa
 * Object explosion
 *
 * Revision 1.9  2005/05/19 13:02:16  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:13  southa
 * Source conditioning
 *
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
