/*
 * $Id: CorePOSIX.h,v 1.2 2002/05/27 12:58:42 southa Exp $
 * $Log: CorePOSIX.h,v $
 * Revision 1.2  2002/05/27 12:58:42  southa
 * GameContract and global configs added
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_SYS_WAIT_H
#include <sys/wait.h>
#define HAVE_POSIX 1
#endif

#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

