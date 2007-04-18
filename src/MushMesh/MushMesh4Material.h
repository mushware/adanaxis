//%includeGuardStart {
#ifndef MUSHMESH4MATERIAL_H
#define MUSHMESH4MATERIAL_H
//%includeGuardStart } A3b7aNTGEOECii2HGCN0kg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Material.h
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
//%Header } id5YjiZjssYtgu03D5JArg
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
