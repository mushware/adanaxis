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
 * $Id: MushModelMultiFacet.h,v 1.4 2005/02/03 21:03:04 southa Exp $
 * $Log: MushModelMultiFacet.h,v $
 * Revision 1.4  2005/02/03 21:03:04  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 * Revision 1.2  2004/01/08 22:41:10  southa
 * MushModel commands
 *
 * Revision 1.1  2004/01/07 18:01:19  southa
 * MushModel and Infernal work
 *
 */

#include "MushModelStandard.h"

#include "MushModelFacet.h"

//:generate virtual standard ostream xml1
class MushModelMultiFacet : public MushcoreVirtualObject
{
public:
    typedef std::vector<MushModelFacet> tContainer;
    typedef tContainer::iterator tIterator;
    typedef tContainer::const_iterator tConstIterator;
    
    MushModelMultiFacet() {}
    virtual ~MushModelMultiFacet() {}

    tIterator FacetsBegin(void) { return m_facets.begin(); }
    tIterator FacetsEnd(void) { return m_facets.end(); }
    tConstIterator FacetsBegin(void) const { return m_facets.begin(); }
    tConstIterator FacetsEnd(void) const { return m_facets.end(); }
    
    static MushcoreScalar MushModelMultiFacetLoad(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static MushcoreScalar MushModelMultiFacetSave(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static MushcoreScalar MushModelMultiFacetPrint(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static void Install(void);
    static void NullFunction(void);
    
private:
    tContainer m_facets; //:readwrite
//%classPrototypes {
public:
    const tContainer& Facets(void) const { return m_facets; }
    void FacetsSet(const tContainer& inValue) { m_facets=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } LkrigpigQgsqXr4Qjn7V1g
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
