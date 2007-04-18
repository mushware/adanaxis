//%includeGuardStart {
#ifndef ADANAXISDATA_H
#define ADANAXISDATA_H
//%includeGuardStart } QmuNClsGkIW/ng3D/NqMXg
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisData.h
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
//%Header } Cej2shXtXrq4p8lgY5jY5A
/*
 * $Id: AdanaxisData.h,v 1.5 2007/04/16 08:41:07 southa Exp $
 * $Log: AdanaxisData.h,v $
 * Revision 1.5  2007/04/16 08:41:07  southa
 * Level and header mods
 *
 * Revision 1.4  2007/03/16 19:50:44  southa
 * Damage indicators
 *
 * Revision 1.3  2006/08/01 17:21:23  southa
 * River demo
 *
 * Revision 1.2  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 */

#include "AdanaxisStandard.h"
#include "AdanaxisSaveData.h"
#include "AdanaxisVolatileData.h"

//:xml1base MushGameData
//:generate virtual standard ostream xml1
class AdanaxisData : public MushGameData
{
public:
    enum
    {
        kCharProjectile = 'f',
        kCharKhazi = 'k'
    };
    typedef AdanaxisSaveData::tProjectile tProjectile;
    typedef AdanaxisSaveData::tProjectileList tProjectileList;
    typedef AdanaxisSaveData::tKhazi tKhazi;
    typedef AdanaxisSaveData::tKhaziList tKhaziList;
    
    AdanaxisData(const std::string& inName="");
    
private:

//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisData& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } LlUrmkG8rsEkpdcd8FoqiA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
