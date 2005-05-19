//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLAppHandler.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } MH7TXJnfOVCfBvXi1shH0g
/*
 * $Id: GLAppHandler.cpp,v 1.24 2004/01/02 21:13:04 southa Exp $
 * $Log: GLAppHandler.cpp,v $
 * Revision 1.24  2004/01/02 21:13:04  southa
 * Source conditioning
 *
 * Revision 1.23  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.22  2003/08/21 23:08:17  southa
 * Fixed file headers
 *
 * Revision 1.21  2003/01/13 14:31:54  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.20  2003/01/09 14:56:57  southa
 * Created Mushcore
 *
 * Revision 1.19  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.18  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.17  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.16  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.15  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.14  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.13  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.12  2002/06/20 15:50:29  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.11  2002/06/06 15:00:44  southa
 * Mouse fixes
 *
 * Revision 1.10  2002/06/06 13:36:13  southa
 * Mouse handling
 *
 * Revision 1.9  2002/06/05 16:29:51  southa
 * Mouse control
 *
 * Revision 1.8  2002/05/31 15:18:15  southa
 * Keyboard reading
 *
 * Revision 1.7  2002/05/24 18:10:43  southa
 * MushcoreXML and game map
 *
 * Revision 1.6  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 * Revision 1.5  2002/05/10 16:41:42  southa
 * Changed .hp files to .h
 *
 * Revision 1.4  2002/05/08 16:31:20  southa
 * Created API directory
 *
 * Revision 1.3  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 * Revision 1.2  2002/02/24 22:49:33  southa
 * Got working under cygwin
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "GLAppHandler.h"
#include "GLStandard.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;
