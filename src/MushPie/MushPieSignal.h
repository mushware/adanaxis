//%includeGuardStart {
#ifndef MUSHPIESIGNAL_H
#define MUSHPIESIGNAL_H
//%includeGuardStart } 4Ppb7qlwhe1x6KEcwB9Qug
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSignal.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } WIDxM2ESAcY9zeM8fx9m/A
/*
 * $Id$
 * $Log$
 */

#include "MushPieStandard.h"

//:generate standard ostream xml1
class MushPieSignal : public MushcoreVirtualObject
{
public:
    MushPieSignal() {}
    virtual ~MushPieSignal() {}
    
private:
    
//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual MushPieSignal *AutoClone(void) const;
    virtual MushPieSignal *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } ILLrDRrOEn4vLolyop8qhg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPieSignal& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } U1OYYIdjfEmHGMjXtntbzw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
