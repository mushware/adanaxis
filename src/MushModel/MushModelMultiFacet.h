//%includeGuardStart {
#ifndef MUSHMODELMULTIFACET_H
#define MUSHMODELMULTIFACET_H
//%includeGuardStart } 8bZtiGayCFUJEjhZHvyTRw
//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelMultiFacet.h
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
//%Header } Q4YwzcDbs4v6cm5wMMUVAg
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
