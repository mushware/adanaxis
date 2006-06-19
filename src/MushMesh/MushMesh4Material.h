//%includeGuardStart {
#ifndef MUSHMESH4MATERIAL_H
#define MUSHMESH4MATERIAL_H
//%includeGuardStart } A3b7aNTGEOECii2HGCN0kg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Material.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } 7UvikX8idpVAxy72TO4JQw
/*
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"

//:generate virtual standard ostream xml1
class MushMesh4Material : public MushcoreVirtualObject
{
public:
private:
	std::string m_name; //:readwrite
	
//%classPrototypes {
public:
    const std::string& Name(void) const { return m_name; }
    void NameSet(const std::string& inValue) { m_name=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 6kS7zAtgsEBxzZKpMEtoHg
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
