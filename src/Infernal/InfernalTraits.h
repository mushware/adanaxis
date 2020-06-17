//%includeGuardStart {
#ifndef INFERNALTRAITS_H
#define INFERNALTRAITS_H
//%includeGuardStart } Ofi9gx/UF+E0TyehI9eX6g
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalTraits.h
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
//%Header } qKNY5dGhyk6v78ZfWMNQVA
/*
 * $Id: InfernalTraits.h,v 1.5 2006/06/01 15:39:07 southa Exp $
 * $Log: InfernalTraits.h,v $
 * Revision 1.5  2006/06/01 15:39:07  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:06  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/04 15:32:12  southa
 * Module split
 *
 * Revision 1.20  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.19  2003/08/21 23:08:58  southa
 * Fixed file headers
 *
 * Revision 1.18  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.17  2003/01/12 17:32:57  southa
 * Mushcore work
 *
 * Revision 1.16  2003/01/11 17:07:52  southa
 * Mushcore library separation
 *
 * Revision 1.15  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
 * Revision 1.14  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.13  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.12  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.10  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 * Revision 1.9  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.8  2002/10/14 15:13:40  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.7  2002/08/27 08:56:27  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/08 14:22:03  southa
 * Rotated desks
 *
 * Revision 1.4  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/04 20:27:37  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.1  2002/06/04 14:12:26  southa
 * Traits loader first stage
 *
 */

#include "mushMushcore.h"

class InfernalTraits : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    InfernalTraits(): m_traitsValid(false) {}
    virtual ~InfernalTraits() {}
    void Verify(void);
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    
protected:
    Mushware::U32 NumberOfTraitsGet(void) const;
    InfernalTraits& TraitsGet(Mushware::U32 inIndex) const;
    const std::string TraitsNameGet(void) const;

    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);    
    
private:
    void NullHandler(MushcoreXML& inXML);
    void HandleBaseEnd(MushcoreXML& inXML);
    void HandleTraitsEnd(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef std::map<std::string, void (InfernalTraits::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;

    void RebuildTraits(void) const;
        
    std::vector<std::string> m_baseNames;
    mutable std::string m_failMessage;
    mutable bool m_traitsValid;
    mutable std::vector<InfernalTraits *> m_baseTraits;
};

inline Mushware::U32
InfernalTraits::NumberOfTraitsGet(void) const
{
    if (!m_traitsValid) RebuildTraits();
    return m_baseTraits.size();
}

inline InfernalTraits&
InfernalTraits::TraitsGet(Mushware::U32 inIndex) const
{
    if (!m_traitsValid)
    {
        throw(MushcoreLogicFail("Use of invalid traits"));
    }
    MUSHCOREASSERT(inIndex < m_baseTraits.size());
    return *m_baseTraits[inIndex];
}

inline std::ostream& operator<<(std::ostream &inOut, const InfernalTraits& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
