//%includeGuardStart {
#ifndef MUSHPIEPOSICITY_H
#define MUSHPIEPOSICITY_H
//%includeGuardStart } F2dkpQPdB/Jt0A6al8mBNQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePosicity.h
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
//%Header } HE528RjL4WRMCMY6TzRyjg
/*
 * $Id: MushPiePosicity.h,v 1.10 2006/06/01 15:39:37 southa Exp $
 * $Log: MushPiePosicity.h,v $
 * Revision 1.10  2006/06/01 15:39:37  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.8  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.7  2005/03/25 19:13:50  southa
 * GameDialogue work
 *
 * Revision 1.6  2005/02/10 12:34:15  southa
 * Template fixes
 *
 * Revision 1.5  2004/01/18 18:25:29  southa
 * XML stream upgrades
 *
 * Revision 1.4  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 * Revision 1.3  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.2  2004/01/05 14:27:41  southa
 * MushPie work and build fixes
 *
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushPieStandard.h"

//:generate virtual standard basic ostream xml1
class MushPiePosicity : public MushcoreVirtualObject
{
public:
    MushPiePosicity() {}
    MushPiePosicity(Mushware::t4Val inPos, Mushware::t4Val inVel, Mushware::tQValPair inAngPos, Mushware::tQValPair inAngVel) :
        m_angPos(inAngPos),
        m_angVel(inAngVel),
        m_pos(inPos),
        m_vel(inVel)
    {
    }

    void InPlaceVelocityAdd(void);
    
private:
    Mushware::tQValPair m_angPos; //:readwrite
    Mushware::tQValPair m_angVel; //:readwrite
    Mushware::t4Val m_pos; //:readwrite
    Mushware::t4Val m_vel; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::tQValPair& AngPos(void) const { return m_angPos; }
    void AngPosSet(const Mushware::tQValPair& inValue) { m_angPos=inValue; }
    const Mushware::tQValPair& AngVel(void) const { return m_angVel; }
    void AngVelSet(const Mushware::tQValPair& inValue) { m_angVel=inValue; }
    const Mushware::t4Val& Pos(void) const { return m_pos; }
    void PosSet(const Mushware::t4Val& inValue) { m_pos=inValue; }
    const Mushware::t4Val& Vel(void) const { return m_vel; }
    void VelSet(const Mushware::t4Val& inValue) { m_vel=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const MushPiePosicity& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 86kDuPoW5V2S4kjphyMulw
};

inline void
MushPiePosicity::InPlaceVelocityAdd(void)
{
    m_pos += m_vel;
    m_angPos.OuterMultiplyBy(m_angVel);
}

//%inlineHeader {

inline bool
operator==(const MushPiePosicity& inA, const MushPiePosicity& inB)
{
    return inA.AutoEquals(inB);
}

inline bool
operator!=(const MushPiePosicity& inA, const MushPiePosicity& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPiePosicity& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } fzs8dJlVZ1sroROUldg9NA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
