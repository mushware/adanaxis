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
 * $Id: MushPieSignal.h,v 1.1 2004/01/10 20:29:35 southa Exp $
 * $Log: MushPieSignal.h,v $
 * Revision 1.1  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 */

#include "MushPieStandard.h"

//:generate virtual standard ostream xml1
class MushPieSignal : public MushcoreVirtualObject
{
public:
    MushPieSignal() {}
    virtual ~MushPieSignal() {}
    
private:
    
//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } FwEN8XJox/Ejr30NeyHzCg
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
