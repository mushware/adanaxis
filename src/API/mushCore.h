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
 * $Id: mushCore.h,v 1.17 2002/12/20 13:17:30 southa Exp $
 * $Log: mushCore.h,v $
 * Revision 1.17  2002/12/20 13:17:30  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.16  2002/12/12 18:38:57  southa
 * Mustl separation
 *
 * Revision 1.15  2002/12/04 12:54:40  southa
 * Network control work
 *
 * Revision 1.14  2002/11/22 11:42:05  southa
 * Added developer controls
 *
 * Revision 1.13  2002/11/14 17:29:07  southa
 * Config database
 *
 * Revision 1.12  2002/11/07 11:59:02  southa
 * Web commands
 *
 * Revision 1.11  2002/10/22 20:41:56  southa
 * Source conditioning
 *
 * Revision 1.10  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/15 13:39:30  southa
 * MushcoreData and MushcoreDatRef
 *
 * Revision 1.8  2002/08/07 13:36:43  southa
 * Conditioned source
 *
 * Revision 1.7  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.6  2002/07/02 15:48:29  southa
 * Floor std::map designer
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
#include "Mushcore/MushcoreAutoMonkey.h"

// Application class required by main()
#include "Mushcore/MushcoreApp.h"

// Application handler subclassed to provide different application types
#include "Mushcore/MushcoreAppHandler.h"

// Command handler to be subclassed to provide new commands
#include "Mushcore/MushcoreCommandHandler.h"

// Configuration handler
#include "Mushcore/MushcoreConfig.h"

// Data storage
#include "Mushcore/MushcoreData.h"

// Data reference
#include "Mushcore/MushcoreDataRef.h"

// Environment
#include "Mushcore/MushcoreEnv.h"

// Environment output controller
#include "Mushcore/MushcoreEnvOutput.h"

// Exception classes to be thrown
#include "Mushcore/MushcoreException.h"

// Global configuration
#include "Mushcore/MushcoreGlobalConfig.h"

// History storage
#include "Mushcore/MushcoreHistory.h"

// Package and version information
#include "Mushcore/MushcoreInfo.h"

// Used as a hook to register classes and commands at startup
#include "Mushcore/MushcoreInstaller.h"

// Command interpreter
#include "Mushcore/MushcoreInterpreter.h"

// Mushcore namespace
#include "Mushcore/MushcoreNamespace.h"

// Pickle utilities
#include "Mushcore/MushcorePickle.h"

// POSIX utilities
#include "Mushcore/MushcorePOSIX.h"

// Regular expression utility
#include "Mushcore/MushcoreRegExp.h"

// Scalar type for expressions
#include "Mushcore/MushcoreScalar.h"

// Script class
#include "Mushcore/MushcoreScript.h"

// Standard typedefs
#include "Mushcore/MushcoreStandard.h"

// Stream utilities
#include "Mushcore/MushcoreStreamUtil.h"

// Compilation switches
#include "Mushcore/MushcoreSwitches.h"

// Utilities
#include "Mushcore/MushcoreUtil.h"

// XML
#include "Mushcore/MushcoreXML.h"

#endif
