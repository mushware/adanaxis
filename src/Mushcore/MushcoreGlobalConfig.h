//%includeGuardStart {
#ifndef MUSHCOREGLOBALCONFIG_H
#define MUSHCOREGLOBALCONFIG_H
//%includeGuardStart } 9JsCIJCzO6xzkid50/w7wg
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreGlobalConfig.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 9zikVlTaKGnD3FaIDO69lQ
/*
 * $Id: MushcoreGlobalConfig.h,v 1.8 2003/08/21 23:09:13 southa Exp $
 * $Log: MushcoreGlobalConfig.h,v $
 * Revision 1.8  2003/08/21 23:09:13  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/20 15:38:28  southa
 * Created MushcoreTest
 *
 * Revision 1.6  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.5  2003/01/18 17:05:47  southa
 * Singleton work
 *
 * Revision 1.4  2003/01/18 13:33:58  southa
 * Created MushcoreSingleton
 *
 * Revision 1.3  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.8  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:41:59  southa
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
 * GameData and loadtilemap command
 *
 * Revision 1.1  2002/05/28 13:07:04  southa
 * Command parser extensions and TIFF loader
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreConfig.h"
#include "MushcoreSingleton.h"

class MushcoreGlobalConfig : public MushcoreConfig, public MushcoreSingleton<MushcoreGlobalConfig>
{
public:
    static void Install(void);
    static void NullFunction(void);

private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
