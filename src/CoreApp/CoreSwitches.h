#ifndef CORESWITCHES_H
#define CORESWITCHES_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: CoreSwitches.h,v 1.2 2002/06/27 12:36:04 southa Exp $
 * $Log: CoreSwitches.h,v $
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

#define CORETESTING(a) a
#define IFCORETESTING(a) a

#define TEXTESTING 0
#define MONKEYTESTING 0
#define FLEXTESTING 0

#if TEXTESTING
#define IFTEXTESTING(a) a
#else
#define IFTEXTESTING(a)
#endif
#if MONKEYTESTING
#define IFMONKEYTESTING(a) a
#else
#define IFMONKEYTESTING(a)
#endif
#if FLEXTESTING
#define IFFLEXTESTING(a) a
#else
#define IFFLEXTESTING(a)
#endif

#endif
