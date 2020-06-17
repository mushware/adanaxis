//%includeGuardStart {
#ifndef MUSHMODELFACET_H
#define MUSHMODELFACET_H
//%includeGuardStart } ekWoJKi499bLm+Eqn8fo/w
//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelFacet.h
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
//%Header } UzNNGn2AksrmcakRoDss0A
/*
 * $Id: MushModelFacet.h,v 1.8 2006/06/01 15:39:35 southa Exp $
 * $Log: MushModelFacet.h,v $
 * Revision 1.8  2006/06/01 15:39:35  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/05/19 13:02:12  southa
 * Mac release work
 *
 * Revision 1.5  2005/02/10 12:34:09  southa
 * Template fixes
 *
 * Revision 1.4  2005/02/03 21:03:03  southa
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

#include "mushGL.h"

#include "MushModelMaterial.h"

//:generate virtual standard ostream xml1
class MushModelFacet : public MushcoreVirtualObject
{
public:
    MushModelFacet() {}
    virtual ~MushModelFacet() {}
    
private:
    std::string m_renderType; //:readwrite
    MushcoreDataRef<MushModelMaterial> m_materialRef; //:readwrite
    std::vector<Mushware::t3Val> m_vertices; //:readwrite
    std::vector< std::vector<Mushware::t4Val> > m_texCoords; //:readwrite
    std::vector<Mushware::t3Val> m_normals; //:readwrite
//%classPrototypes {
public:
    const std::string& RenderType(void) const { return m_renderType; }
    void RenderTypeSet(const std::string& inValue) { m_renderType=inValue; }
    const MushcoreDataRef<MushModelMaterial>& MaterialRef(void) const { return m_materialRef; }
    void MaterialRefSet(const MushcoreDataRef<MushModelMaterial>& inValue) { m_materialRef=inValue; }
    const std::vector<Mushware::t3Val>& Vertices(void) const { return m_vertices; }
    void VerticesSet(const std::vector<Mushware::t3Val>& inValue) { m_vertices=inValue; }
    const std::vector< std::vector<Mushware::t4Val> >& TexCoords(void) const { return m_texCoords; }
    void TexCoordsSet(const std::vector< std::vector<Mushware::t4Val> >& inValue) { m_texCoords=inValue; }
    const std::vector<Mushware::t3Val>& Normals(void) const { return m_normals; }
    void NormalsSet(const std::vector<Mushware::t3Val>& inValue) { m_normals=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Yz7GKVZK6et6uG4rk72AKw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushModelFacet& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 03eBAmcmyjJc7hMFTGzhZQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
