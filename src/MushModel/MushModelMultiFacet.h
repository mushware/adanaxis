//%includeGuardStart {
#ifndef MUSHMODELMULTIFACET_H
#define MUSHMODELMULTIFACET_H
//%includeGuardStart } 8bZtiGayCFUJEjhZHvyTRw
//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelMultiFacet.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } TX3nuuL5kxBkNIyARfQDOA
/*
 * $Id$
 * $Log$
 */

#include "MushModelStandard.h"

#include "MushModelFacet.h"

//:generate standard ostream xml1
class MushModelMultiFacet : public MushcoreVirtualObject
{
public:
    MushModelMultiFacet() {}
    virtual ~MushModelMultiFacet() {}

private:
    std::vector<MushModelFacet> m_facets; //:readwrite
//%classPrototypes {
public:
    const std::vector<MushModelFacet>& FacetsGet(void) const { return m_facets; }
    void FacetsSet(const std::vector<MushModelFacet>& inValue) { m_facets=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushModelMultiFacet *AutoClone(void) const;
    virtual MushModelMultiFacet *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } C0wEDaeexgMajMwcHzgPGg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushModelMultiFacet& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } CHNgmHF9a5tHaMgqHTInCg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
