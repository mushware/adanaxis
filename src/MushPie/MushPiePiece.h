//%includeGuardStart {
#ifndef MUSHPIEPIECE_H
#define MUSHPIEPIECE_H
//%includeGuardStart } 0PLScWvXTetFOnepxmZBkg
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePiece.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } natnLnIxDQDAAFW/Brzh3g
/*
 * $Id: MushPiePiece.h,v 1.7 2004/01/06 10:08:51 southa Exp $
 * $Log: MushPiePiece.h,v $
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

//:generate standard ostream xml1 basic
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
    const tSleepState& SleepStateGet(void) const { return m_sleepState; }
    void SleepStateSet(const tSleepState& inValue) { m_sleepState=inValue; }
    const MushPieForm::tDataRef& FormRefGet(void) const { return m_formRef; }
    void FormRefSet(const MushPieForm::tDataRef& inValue) { m_formRef=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushPiePiece *AutoClone(void) const;
    virtual MushPiePiece *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    bool AutoEquals(const MushPiePiece& inObj) const;
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 3gpOwTzsXdWBTliRUviRyg
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
