#ifndef CORESWITCHES_H
#define CORESWITCHES_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: CoreSwitches.h,v 1.6 2002/10/22 20:41:59 southa Exp $
 * $Log: CoreSwitches.h,v $
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
