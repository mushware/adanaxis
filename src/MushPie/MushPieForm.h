//%includeGuardStart {
#ifndef MUSHPIEFORM_H
#define MUSHPIEFORM_H
//%includeGuardStart } chr+rdZQI8cOcPal/mrI9Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieForm.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } GYyeLc+epGQUElec/y5hZA
/*
 * $Id$
 * $Log$
 */

#include "MushPieStandard.h"

//:generate standard ostream xml1
class MushPieForm : public MushcoreVirtualObject
{
public:
    typedef MushcoreData<MushPieForm *, Mushware::U32> tData;
    typedef MushcoreDataRef<MushPieForm *, Mushware::U32> tDataRef;
    
    MushPieForm() {}
    virtual ~MushPieForm() {}
//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual MushPieForm *AutoClone(void) const;
    virtual MushPieForm *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } nJdV43qCi9casKf4eWO8BA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPieForm& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } t8f6LLmjLkfX4mZD/ckOag
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
