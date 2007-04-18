//%includeGuardStart {
#ifndef MUSHMODELMULTIFACET_H
#define MUSHMODELMULTIFACET_H
//%includeGuardStart } 8bZtiGayCFUJEjhZHvyTRw
//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelMultiFacet.h
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } f9u/ZdABDno7Vvtb2vRySw
/*
 * $Id: MushModelMultiFacet.h,v 1.8 2006/06/01 15:39:35 southa Exp $
 * $Log: MushModelMultiFacet.h,v $
 * Revision 1.8  2006/06/01 15:39:35  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/05/19 13:02:12  southa
 * Mac release work
 *
 * Revision 1.5  2005/02/10 12:34:10  southa
 * Template fixes
 *
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
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } i591tBuSFPD9cd+MkDIoaQ
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
