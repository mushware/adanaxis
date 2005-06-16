//%includeGuardStart {
#ifndef ADANAXISSAVEDATA_H
#define ADANAXISSAVEDATA_H
//%includeGuardStart } Phse6V6gEtb3LIdaz1rQlw
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisSaveData.h
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } lP1KYvwjO8U4fVO07cIsNw
/*
 * $Id: AdanaxisSaveData.h,v 1.1 2005/06/14 20:39:40 southa Exp $
 * $Log: AdanaxisSaveData.h,v $
 * Revision 1.1  2005/06/14 20:39:40  southa
 * Adanaxis work
 *
 */

#include "AdanaxisStandard.h"

#include "API/mushGame.h"
#include "API/mushMushGame.h"

//:xml1base MushGameSaveData
//:generate virtual standard ostream xml1
class AdanaxisSaveData : public MushGameSaveData
{
public:
    
private:
    MushcoreData<GameDialogue> m_dialogues; //:readwrite :wref
//%classPrototypes {
public:
    const MushcoreData<GameDialogue>& Dialogues(void) const { return m_dialogues; }
    void DialoguesSet(const MushcoreData<GameDialogue>& inValue) { m_dialogues=inValue; }
    // Writable reference for m_dialogues
    MushcoreData<GameDialogue>& DialoguesWRef(void) { return m_dialogues; }
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } OvDEOoXgN9lJ61LWI79PtQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisSaveData& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } +jNhUDLSnXe2KY7BCQ1TrA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
