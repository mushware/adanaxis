//%includeGuardStart {
#ifndef MUSHGAMEPIECE_H
#define MUSHGAMEPIECE_H
//%includeGuardStart } fXnM4FD/EmJAfw+g836GPQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGamePiece.h
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
//%Header } T/MWnTXtRKRQsmRlB17JyQ
/*
 * $Id: MushGamePiece.h,v 1.6 2005/07/07 16:54:17 southa Exp $
 * $Log: MushGamePiece.h,v $
 * Revision 1.6  2005/07/07 16:54:17  southa
 * Control tweaks
 *
 * Revision 1.5  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.4  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/07/01 16:42:54  southa
 * Render work
 *
 * Revision 1.2  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.1  2005/06/24 10:30:12  southa
 * MushGame camera work
 *
 */

#include "MushGameStandard.h"

class MushGameLogic;
class MushGameMessage;

#include "API/mushMushMesh.h"

//:generate virtual standard ostream xml1
class MushGamePiece : public MushcoreVirtualObject
{
public:
    MushGamePiece();
    virtual ~MushGamePiece() {}
    virtual void PreControl(MushGameLogic& ioLogic) {}
    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice) {}
    
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);

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
operator<<(std::ostream& ioOut, const MushGamePiece& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } hzo4AnwoYg7g4RrSJcViWQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
