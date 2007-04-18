//%includeGuardStart {
#ifndef ADANAXISUTIL_H
#define ADANAXISUTIL_H
//%includeGuardStart } xu4PJKjPyonUX1Z4uvxgtQ
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisUtil.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 8jRHljgRChkKMERROh6Eag
/*
 * $Id: AdanaxisUtil.h,v 1.17 2007/04/16 08:41:09 southa Exp $
 * $Log: AdanaxisUtil.h,v $
 * Revision 1.17  2007/04/16 08:41:09  southa
 * Level and header mods
 *
 * Revision 1.16  2007/03/12 21:06:00  southa
 * Scanner symbols
 *
 * Revision 1.15  2007/03/09 19:50:12  southa
 * Resident textures
 *
 * Revision 1.14  2007/03/07 11:29:25  southa
 * Level permission
 *
 * Revision 1.13  2006/12/18 15:39:35  southa
 * Palette changes
 *
 * Revision 1.12  2006/10/05 15:39:17  southa
 * Explosion handling
 *
 * Revision 1.11  2006/08/01 17:21:30  southa
 * River demo
 *
 * Revision 1.10  2006/07/19 14:34:52  southa
 * Flare effects
 *
 * Revision 1.9  2006/06/21 12:17:57  southa
 * Ruby object generation
 *
 * Revision 1.8  2006/06/01 15:38:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/09/05 12:54:29  southa
 * Solid rendering work
 *
 * Revision 1.6  2005/08/29 18:40:56  southa
 * Solid rendering work
 *
 * Revision 1.5  2005/08/01 20:24:15  southa
 * Backdrop and build fixes
 *
 * Revision 1.4  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.3  2005/07/12 12:18:17  southa
 * Projectile work
 *
 * Revision 1.2  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.1  2005/06/30 16:29:24  southa
 * Adanaxis work
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisLogic.h"

class AdanaxisAppHandler;
class AdanaxisConfig;
class AdanaxisMeshLibrary;

class AdanaxisUtil
{
public:
    static void MissingSkinsCreate(AdanaxisLogic& ioLogic);
    static void MeshPurge(AdanaxisLogic& ioLogic);
    static void TestPiecesCreate(AdanaxisLogic& ioLogic);
    static void TestDecoCreate(AdanaxisLogic& ioLogic);
    static void TestSkinsCreate(AdanaxisLogic& ioLogic);
    static void EmberCreate(AdanaxisLogic& ioLogic, const MushMeshPosticity& inPost, Mushware::tVal inSize, Mushware::tVal inSpeed);
    static void FlareCreate(AdanaxisLogic& ioLogic, const MushMeshPosticity& inPost, Mushware::tVal inSize, Mushware::tVal inSpeed);
    static void ExploCreate(AdanaxisLogic& ioLogic, const MushMeshPosticity& inPost, Mushware::tVal inSize, Mushware::tVal inSpeed);
    
    static AdanaxisAppHandler& AppHandler(void);
    static const AdanaxisConfig& Config(void);
    static AdanaxisConfig& ConfigWRef(void);
    static AdanaxisMeshLibrary& MeshLibrary(void);
    static AdanaxisLogic& Logic(MushGameLogic& ioLogic);
};

inline AdanaxisLogic&
AdanaxisUtil::Logic(MushGameLogic& ioLogic)
{
    AdanaxisLogic *pLogic = dynamic_cast<AdanaxisLogic *>(&ioLogic);
    if (pLogic == NULL)
    {
        throw MushcoreLogicFail("AdanaxisLogic of wrong type");
    }
    return *pLogic;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
