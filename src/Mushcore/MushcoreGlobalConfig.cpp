//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreGlobalConfig.cpp
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
//%Header } n/q3I9GHluKmfaL2oxRr1Q
/*
 * $Id: MushcoreGlobalConfig.cpp,v 1.9 2004/01/02 21:13:12 southa Exp $
 * $Log: MushcoreGlobalConfig.cpp,v $
 * Revision 1.9  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.8  2003/10/04 12:23:08  southa
 * File renaming
 *
 * Revision 1.7  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:12  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.4  2003/01/18 13:33:58  southa
 * Created MushcoreSingleton
 *
 * Revision 1.3  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.2  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.8  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/30 14:41:15  southa
 * InfernalData and loadtilemap command
 *
 * Revision 1.1  2002/05/28 13:07:04  southa
 * Command parser extensions and TIFF loader
 *
 */

#include "MushcoreGlobalConfig.h"

#include "MushcoreEnv.h"
#include "MushcoreInstaller.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushcoreGlobalConfig);

MushcoreInstaller
MushcoreGlobalConfig(MushcoreGlobalConfig::Install);

void
MushcoreGlobalConfig::Install(void)
{
    MushcoreEnv::Sgl().PushConfig(Sgl());
}

void
MushcoreGlobalConfig::NullFunction(void)
{
}    
