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
 * $Id: InfernalForm.h,v 1.3 2005/02/03 21:02:55 southa Exp $
 * $Log: InfernalForm.h,v $
 * Revision 1.3  2005/02/03 21:02:55  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 * Revision 1.1  2004/01/07 18:01:18  southa
 * MushModel and Infernal work
 *
 */

#include "InfernalStandard.h"

#include "InfernalFacetContext.h"

#include "mushGL.h"

//:xml1base MushPieForm
//:generate virtual standard ostream xml1
class InfernalForm : public MushPieForm
{
public:
    enum SignalNumbers
    {
        kSignalInvalid,
        kSignalNone,
        kSignalRender
    };
    
    InfernalForm() : m_facetContextIndex(0) {}
    virtual ~InfernalForm() {}

    virtual void SignalHandle(const MushPieSignal& inSignal);

    static MushcoreScalar InfernalFormLoad(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static MushcoreScalar InfernalFormSave(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static MushcoreScalar InfernalFormPrint(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static void Install(void);
    
private:
    void Render(void);
        
    MushcoreDataRef<MushModelMultiFacet> m_modelRef; //:readwrite

    std::vector<InfernalFacetContext> m_facetContexts;
    Mushware::U32 m_facetContextIndex;
    
//%classPrototypes {
public:
    const MushcoreDataRef<MushModelMultiFacet>& ModelRef(void) const { return m_modelRef; }
    void ModelRefSet(const MushcoreDataRef<MushModelMultiFacet>& inValue) { m_modelRef=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } FNWoO0wm7YuOJm09XR2ZCw
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
