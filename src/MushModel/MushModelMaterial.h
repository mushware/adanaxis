//%includeGuardStart {
#ifndef MUSHMODELMATERIAL_H
#define MUSHMODELMATERIAL_H
//%includeGuardStart } MVAhHqvTFcPat6v7aL8ofA
//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelMaterial.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } Tp30nJVgVlLDOVsxZYAjMg
/*
 * $Id: MushModelMaterial.h,v 1.5 2005/02/10 12:34:09 southa Exp $
 * $Log: MushModelMaterial.h,v $
 * Revision 1.5  2005/02/10 12:34:09  southa
 * Template fixes
 *
 * Revision 1.4  2005/02/03 21:03:03  southa
 * Build fixes
 *
 * Revision 1.3  2004/09/27 22:42:09  southa
 * MSVC compilation fixes
 *
 * Revision 1.2  2004/01/08 22:41:10  southa
 * MushModel commands
 *
 * Revision 1.1  2004/01/07 18:01:19  southa
 * MushModel and Infernal work
 *
 */

#include "MushModelStandard.h"

//:generate virtual standard ostream xml1
class MushModelMaterial : public MushcoreVirtualObject
{
public:
    MushModelMaterial() {}
    virtual ~MushModelMaterial() {}
    
    static MushcoreScalar MushModelMaterialLoad(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static MushcoreScalar MushModelMaterialSave(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static MushcoreScalar MushModelMaterialPrint(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static void Install(void);
    static void NullFunction(void);
    
private:
    std::string m_textureName; //:readwrite
//%classPrototypes {
public:
    const std::string& TextureName(void) const { return m_textureName; }
    void TextureNameSet(const std::string& inValue) { m_textureName=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } pcn6vWA1w99VA8+fQWh9qQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushModelMaterial& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 6lnOo2TAm92GhWgqIKM4Dg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
