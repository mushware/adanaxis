//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLRenderable.cpp
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
//%Header } 3lA+kfvW1aQORIPIFmGN9A
/*
 * $Id: GLRenderable.cpp,v 1.10 2004/01/02 21:13:05 southa Exp $
 * $Log: GLRenderable.cpp,v $
 * Revision 1.10  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.9  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:27  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.6  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.5  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 */

#include "GLRenderable.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

