//%includeGuardStart {
#ifndef MUSHPIEPIECEMOBILE_H
#define MUSHPIEPIECEMOBILE_H
//%includeGuardStart } EN3IDI1/oGAnSKUZSf9VkA
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePieceMobile.h
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
//%Header } zYJjcvXk1CkFVFKUZ6UlwA
/*
 * $Id: MushPiePieceMobile.h,v 1.8 2006/06/01 15:39:36 southa Exp $
 * $Log: MushPiePieceMobile.h,v $
 * Revision 1.8  2006/06/01 15:39:36  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.5  2005/02/10 12:34:14  southa
 * Template fixes
 *
 * Revision 1.4  2005/02/01 13:40:37  southa
 * Rotating spheres and hypercube
 *
 * Revision 1.3  2004/09/27 22:42:10  southa
 * MSVC compilation fixes
 *
 * Revision 1.2  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushPieStandard.h"

#include "MushPiePieceSimple.h"
#include "MushPiePosicity.h"

//:xml1base MushPiePiece
//:generate virtual ostream xml1 standard
class MushPiePieceMobile : public MushPiePiece
{
public:
    MushPiePieceMobile();
    virtual ~MushPiePieceMobile() {}
    
    const MushPiePosicity& CurrentPosGet(void) const { return m_currentPosIndex?m_pos1:m_pos0; }
    const MushPiePosicity& NewPosGet(void) const { return m_newPosIndex?m_pos1:m_pos0; }
    void NewPosSet(const MushPiePosicity& inValue) { (m_newPosIndex?m_pos1:m_pos0)=inValue; }
    
    void PosSwap(void);
        
private:
    MushPiePosicity m_pos0;
    MushPiePosicity m_pos1;
    Mushware::U32 m_currentPosIndex;
    Mushware::U32 m_newPosIndex;
    
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};

inline void
MushPiePieceMobile::PosSwap(void)
{
    std::swap(m_currentPosIndex, m_newPosIndex);
};


//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPiePieceMobile& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } TbJaPMFRML9rFgeE6oksyQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
