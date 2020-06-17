//%includeGuardStart {
#ifndef INFERNALFORM_H
#define INFERNALFORM_H
//%includeGuardStart } V1ag6eA66jvA41iK5CZrJw
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalForm.h
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
//%Header } DUd5LWNys/27nDp80pjxFw
/*
 * $Id: InfernalForm.h,v 1.7 2006/06/01 15:39:03 southa Exp $
 * $Log: InfernalForm.h,v $
 * Revision 1.7  2006/06/01 15:39:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/06/20 14:30:35  southa
 * Adanaxis work
 *
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
