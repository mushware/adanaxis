#ifndef CORESWITCHES_HP
#define CORESWITCHES_HP
/*
 * $Id: CoreSwitches.h,v 1.2 2002/03/18 22:21:12 southa Exp $
 * $Log: CoreSwitches.h,v $
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
