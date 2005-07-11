//%includeGuardStart {
#ifndef MUSHGAMEMESSAGEUPLINKPIECE_H
#define MUSHGAMEMESSAGEUPLINKPIECE_H
//%includeGuardStart } TOTGErNU987aoOImssnOHw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageUplinkPiece.h
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
//%Header } 0n7NVZ2LB6nxLC3rOPUIEA
/*
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

#include "MushGameMessage.h"

//:xml1base MushGameMessage
//:generate standard ostream xml1
class MushGameMessageUplinkPiece : public MushGameMessage
{
public:
    explicit MushGameMessageUplinkPiece(const std::string& inID = "") : MushGameMessage(inID) {}
    virtual ~MushGameMessageUplinkPiece() {}

private:
    MushMeshPosticity m_post; //:readwrite :wref
    
//%classPrototypes {
public:
    const MushMeshPosticity& Post(void) const { return m_post; }
    void PostSet(const MushMeshPosticity& inValue) { m_post=inValue; }
    // Writable reference for m_post
    MushMeshPosticity& PostWRef(void) { return m_post; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } xgYH1Kh+PR9uvdS4XNL1+w
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessageUplinkPiece& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } TSLzgxNvUjvIdIMdjN/n+Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
