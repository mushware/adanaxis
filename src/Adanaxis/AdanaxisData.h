//%includeGuardStart {
#ifndef ADANAXISDATA_H
#define ADANAXISDATA_H
//%includeGuardStart } QmuNClsGkIW/ng3D/NqMXg
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisData.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } ARXyRfNIS8PEvXhCR9j6Bg
/*
 * $Id: AdanaxisData.h,v 1.7 2007/04/21 09:41:06 southa Exp $
 * $Log: AdanaxisData.h,v $
 * Revision 1.7  2007/04/21 09:41:06  southa
 * Level work
 *
 * Revision 1.6  2007/04/18 09:22:00  southa
 * Header and level fixes
 *
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
        kCharKhazi = 'k',
        
        // PrimaryType must match values in AdanaxisSpace.rb
        kPrimaryTypeNone = 0,
        kPrimaryTypeRed = 1,
        kPrimaryTypeBlue = 2
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
