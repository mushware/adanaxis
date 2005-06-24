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
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

#include "API/mushMushMesh.h"

//:generate virtual standard ostream xml1
class MushGamePiece : public MushcoreVirtualObject
{
public:
    virtual ~MushGamePiece() {}
    
private:
    MushMeshPosticity m_posticity; //:readwrite :wref
    
//%classPrototypes {
public:
    const MushMeshPosticity& Posticity(void) const { return m_posticity; }
    void PosticitySet(const MushMeshPosticity& inValue) { m_posticity=inValue; }
    // Writable reference for m_posticity
    MushMeshPosticity& PosticityWRef(void) { return m_posticity; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } hHRy4DMAXjZ4wd3zTByMsQ
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
