/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: mushCore.h,v 1.10 2002/08/27 08:56:15 southa Exp $
 * $Log: mushCore.h,v $
 * Revision 1.10  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/15 13:39:30  southa
 * CoreData and CoreDatRef
 *
 * Revision 1.8  2002/08/07 13:36:43  southa
 * Conditioned source
 *
 * Revision 1.7  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.6  2002/07/02 15:48:29  southa
 * Floor map designer
 *
 * Revision 1.5  2002/06/27 12:36:01  southa
 * Build process fixes
 *
 * Revision 1.4  2002/05/30 16:20:53  southa
 * Pickleable GameContract
 *
 * Revision 1.3  2002/05/27 12:58:42  southa
 * GameContract and global configs added
 *
 * Revision 1.2  2002/05/24 16:23:08  southa
 * Config and typenames
 *
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
#include "CoreApp/CoreAutoMonkey.h"

// Application class required by main()
#include "CoreApp/CoreApp.h"

// Application handler subclassed to provide different application types
#include "CoreApp/CoreAppHandler.h"

// Command handler to be subclassed to provide new commands
#include "CoreApp/CoreCommandHandler.h"

// Configuration handler
#include "CoreApp/CoreConfig.h"

// Data storage
#include "CoreApp/CoreData.h"

// Data reference
#include "CoreApp/CoreDataRef.h"

// Exception classes to be thrown
#include "CoreApp/CoreException.h"

// Global configuration
#include "CoreApp/CoreGlobalConfig.h"

// Used as a hook to register classes and commands at startup
#include "CoreApp/CoreInstaller.h"

// POSIX utilities
#include "CoreApp/CorePOSIX.h"

// Regular expression utility
#include "CoreApp/CoreRegExp.h"

// Scalar type for expressions
#include "CoreApp/CoreScalar.h"

// Script class
#include "CoreApp/CoreScript.h"

// Standard typedefs
#include "CoreApp/CoreStandard.h"

// Stream utilities
#include "CoreApp/CoreStreamUtil.h"

// Compilation switches
#include "CoreApp/CoreSwitches.h"

// Utilities
#include "CoreApp/CoreUtil.h"

// Temporary
#include "CoreApp/Dataset.h"

#endif
