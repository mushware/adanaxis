//%includeGuardStart {
#ifndef MUSHPIEPIECE_H
#define MUSHPIEPIECE_H
//%includeGuardStart } 0PLScWvXTetFOnepxmZBkg
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePiece.h
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
//%Header } bLWcqZiLGDFRgRVeCcr7Mw
/*
 * $Id: MushPiePiece.h,v 1.12 2005/05/19 13:02:13 southa Exp $
 * $Log: MushPiePiece.h,v $
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
