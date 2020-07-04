//%includeGuardStart {
#ifndef MUSHMESH4MATERIAL_H
#define MUSHMESH4MATERIAL_H
//%includeGuardStart } A3b7aNTGEOECii2HGCN0kg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Material.h
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
//%Header } T5YgWyEiy1Lkvv9DW+Osrw
/*
 * $Id: MushMesh4Material.h,v 1.2 2006/10/19 15:41:36 southa Exp $
 * $Log: MushMesh4Material.h,v $
 * Revision 1.2  2006/10/19 15:41:36  southa
 * Item handling
 *
 * Revision 1.1  2006/06/19 15:57:18  southa
 * Materials
 *
 */

#include "MushMeshStandard.h"

//:generate virtual standard ostream xml1
class MushMesh4Material : public MushcoreVirtualObject
{
public:
    MushMesh4Material() : m_mappingType(kMappingTypeNone) {}
    enum
    {
        kMappingTypeInvalid,
        kMappingTypeNone,
        kMappingTypeTiled,
        kMappingTypeSingular
    };
    
private:
	std::string m_name; //:readwrite
    Mushware::U32 m_mappingType; //:readwrite
    
//%classPrototypes {
public:
    const std::string& Name(void) const { return m_name; }
    void NameSet(const std::string& inValue) { m_name=inValue; }
    const Mushware::U32& MappingType(void) const { return m_mappingType; }
    void MappingTypeSet(const Mushware::U32& inValue) { m_mappingType=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } BCTgrfjsVXpOaiMDcqVlqg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMesh4Material& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Yi/YS2Nl89AC612pXhszJw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
