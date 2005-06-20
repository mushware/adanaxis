//%includeGuardStart {
#ifndef INFERNALFORM_H
#define INFERNALFORM_H
//%includeGuardStart } V1ag6eA66jvA41iK5CZrJw
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalForm.h
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
//%Header } rsuFpRZmb7Y0Qqq+tToTYg
/*
 * $Id: InfernalForm.h,v 1.5 2005/05/19 13:02:05 southa Exp $
 * $Log: InfernalForm.h,v $
 * Revision 1.5  2005/05/19 13:02:05  southa
 * Mac release work
 *
 * Revision 1.4  2005/02/10 12:34:01  southa
 * Template fixes
 *
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
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } jO8mfLjDpCv2Pk7fo8SyUA
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
