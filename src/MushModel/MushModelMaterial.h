//%includeGuardStart {
#ifndef MUSHMODELMATERIAL_H
#define MUSHMODELMATERIAL_H
//%includeGuardStart } MVAhHqvTFcPat6v7aL8ofA
//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelMaterial.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } NPCsJXr5ecNdynBZmJZGJg
/*
 * $Id: MushModelMaterial.h,v 1.3 2004/09/27 22:42:09 southa Exp $
 * $Log: MushModelMaterial.h,v $
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

//:generate standard ostream xml1
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
    virtual MushModelMaterial *AutoClone(void) const;
    virtual MushModelMaterial *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 6CsW+eA7VnBQiQtLIoBL9w
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
