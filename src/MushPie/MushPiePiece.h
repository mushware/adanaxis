//%includeGuardStart {
#ifndef MUSHPIEPIECE_H
#define MUSHPIEPIECE_H
//%includeGuardStart } 0PLScWvXTetFOnepxmZBkg
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePiece.h
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
//%Header } Q0OPwNqSTDI96pjDDTLzLw
/*
 * $Id: MushPiePiece.h,v 1.14 2006/06/01 15:39:36 southa Exp $
 * $Log: MushPiePiece.h,v $
 * Revision 1.14  2006/06/01 15:39:36  southa
 * DrawArray verification and fixes
 *
 * Revision 1.13  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.12  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.11  2005/02/10 12:34:13  southa
 * Template fixes
 *
 * Revision 1.10  2005/02/03 21:03:05  southa
 * Build fixes
 *
 * Revision 1.9  2004/09/27 22:42:10  southa
 * MSVC compilation fixes
 *
 * Revision 1.8  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.7  2004/01/06 10:08:51  southa
 * MushcoreData and MushPieForm work
 *
 * Revision 1.6  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.5  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.4  2004/01/04 14:36:37  southa
 * Handle 'inline' in source conditioner
 *
 * Revision 1.3  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.2  2004/01/02 17:31:48  southa
 * MushPie work and XML fixes
 *
 * Revision 1.1  2004/01/02 11:57:47  southa
 * Created
 *
 */

#include "MushPieStandard.h"

#include "MushPieForm.h"

// Concrete base class for pieces containing only the mandatory elements

//:generate virtual standard ostream xml1 basic
class MushPiePiece : public MushcoreVirtualObject
{
public:
    enum tSleepState
    {
        kSleepStateInvalid,
        kSleepStateSleeping,
        kSleepStateAwake
    };
    
    MushPiePiece() {}
    virtual ~MushPiePiece() {}
    
protected:
        
private:
    tSleepState m_sleepState; //:readwrite
    MushPieForm::tDataRef m_formRef; //:readwrite
    
//%classPrototypes {
public:
    const tSleepState& SleepState(void) const { return m_sleepState; }
    void SleepStateSet(const tSleepState& inValue) { m_sleepState=inValue; }
    const MushPieForm::tDataRef& FormRef(void) const { return m_formRef; }
    void FormRefSet(const MushPieForm::tDataRef& inValue) { m_formRef=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const MushPiePiece& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 4ytsmnByOpLZXbcJcb0sOQ
};
//%inlineHeader {

inline bool
operator==(const MushPiePiece& inA, const MushPiePiece& inB)
{
    return inA.AutoEquals(inB);
}

inline bool
operator!=(const MushPiePiece& inA, const MushPiePiece& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPiePiece& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } aZXHQOXCZxnWlEyCRUxjGg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
