/*
 * $Id: mushCore.h,v 1.1 2002/05/10 16:39:34 southa Exp $
 * $Log: mushCore.h,v $
 * Revision 1.1  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.4  2002/05/09 18:01:39  southa
 * Rebuild under cygwin
 *
 * Revision 1.3  2002/05/09 17:08:07  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.2  2002/05/08 17:27:39  southa
 * API tidying
 *
 * Revision 1.1  2002/05/08 16:31:23  southa
 * Created API directory
 *
 */
#ifndef MUSHCORE_H
#define MUSHCORE_H

// Utility for memory management
#include "CoreApp/AutoMonkey.h"

// Application class required by main()
#include "CoreApp/CoreApp.h"

// Application handler subclassed to provide different application types
#include "CoreApp/CoreAppHandler.h"

// Command handler to be subclassed to provide new commands
#include "CoreApp/CoreCommandHandler.h"

// Configuration handler
#include "CoreApp/CoreConfig.h"

// Exception classes to be thrown
#include "CoreApp/CoreException.h"

// Used as a hook to register classes and commands at startup
#include "CoreApp/CoreInstaller.h"

// POSIX utilities
#include "CoreApp/CorePOSIX.h"

// Regular expression utility
#include "CoreApp/CoreRegExp.h"

// Standard typedefs
#include "CoreApp/CoreStandard.h"

// Stream utilities
#include "CoreApp/StreamUtil.h"

// Compilation switches
#include "CoreApp/CoreSwitches.h"

// Utilities
#include "CoreApp/CoreUtil.h"

// Temporary
#include "CoreApp/Dataset.h"

#endif
