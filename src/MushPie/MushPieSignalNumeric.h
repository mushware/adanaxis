//%includeGuardStart {
#ifndef MUSHPIESIGNALNUMERIC_H
#define MUSHPIESIGNALNUMERIC_H
//%includeGuardStart } GfddsmMvUhs6Hi7kTC+NGA
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSignalNumeric.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } FOmNozUEFEVBx83/GMJVjA
/*
 * $Id: MushPieSignalNumeric.h,v 1.1 2004/01/10 20:29:35 southa Exp $
 * $Log: MushPieSignalNumeric.h,v $
 * Revision 1.1  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 */

#include "MushPieStandard.h"

#include "MushPieSignal.h"

//:generate standard ostream xml1
class MushPieSignalNumeric : public MushPieSignal
{
public:
    MushPieSignalNumeric() : m_eventNumber(0) {}
    explicit MushPieSignalNumeric(Mushware::U32 inEventNumber) : m_eventNumber(inEventNumber) {}
    virtual ~MushPieSignalNumeric() {}
    
private:
    Mushware::U32 m_eventNumber; //:read
//%classPrototypes {
public:
    const Mushware::U32& EventNumber(void) const { return m_eventNumber; }
    virtual const char *AutoNameGet(void) const;
    virtual MushPieSignalNumeric *AutoClone(void) const;
    virtual MushPieSignalNumeric *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } IzCQ0YOxia+FsktR1dBohw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPieSignalNumeric& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } woqyvkQc0XgwBloUTmMO1A
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
