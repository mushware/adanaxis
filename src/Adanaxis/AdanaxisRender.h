//%includeGuardStart {
#ifndef ADANAXISRENDER_H
#define ADANAXISRENDER_H
//%includeGuardStart } dZcfmpPUzEwmX2Q78sGR/A
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRender.h
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ApiIiDIkgHS1hGasLAa6EQ
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisStandard.h"

#include "API/mushMushGame.h"

//:generate standard ostream xml1
class AdanaxisRender : public MushGameRender
{
public:
    virtual ~AdanaxisRender() {}
    
    virtual void FrameRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera);

private:
//%classPrototypes {
public:
    const char *AutoName(void) const;
    MushcoreVirtualObject *AutoClone(void) const;
    MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } oLR0tLUUWStTX02QfMX/OA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisRender& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } zxkPtj57KCCMub1Z+D17AQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
