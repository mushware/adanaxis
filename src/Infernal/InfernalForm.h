//%includeGuardStart {
#ifndef INFERNALFORM_H
#define INFERNALFORM_H
//%includeGuardStart } V1ag6eA66jvA41iK5CZrJw
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalForm.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } VxPQKKFlOK3QVRP/hQqigA
/*
 * $Id$
 * $Log$
 */

#include "InfernalStandard.h"

//:xml1base MushPieForm
//:generate standard ostream xml1
class InfernalForm : public MushPieForm
{
public:
    InfernalForm() {}
    virtual ~InfernalForm() {}
    
private:
    MushcoreDataRef<MushModelMultiFacet> m_modelRef; //:readwrite
    
//%classPrototypes {
public:
    const MushcoreDataRef<MushModelMultiFacet>& ModelRefGet(void) const { return m_modelRef; }
    void ModelRefSet(const MushcoreDataRef<MushModelMultiFacet>& inValue) { m_modelRef=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual InfernalForm *AutoClone(void) const;
    virtual InfernalForm *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } R0Vf/5HFz3j/luwFLpce9w
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const InfernalForm& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } OwSY6C5EHqSnEeAO1p0UGw


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
