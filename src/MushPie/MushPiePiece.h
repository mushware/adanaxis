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
 * $Id$
 * $Log$
 */

#include "MushPieStandard.h"

#include "MushMesh.h"

// Concrete base class for pieces containing only the mandatory elements

//:generate standard ostream xml1
class MushPiePiece : public MushcoreVirtualObject
{
public:
    MushPiePiece() {}
    virtual ~MushPiePiece() {}
    
protected:
        
private:
    Mushware::t3Val m_position; //:readwrite
    Mushware::t3Val m_velocity; //:readwrite
//%classPrototypes {
public:
    const Mushware::t3Val& PositionGet(void) const { return m_position; }
    void PositionSet(const Mushware::t3Val& inValue) { m_position=inValue; }
    const Mushware::t3Val& VelocityGet(void) const { return m_velocity; }
    void VelocitySet(const Mushware::t3Val& inValue) { m_velocity=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushPiePiece *AutoClone(void) const;
    virtual MushPiePiece *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    void AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } XVSyDhcGgWTNl9KqIfMpWQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPiePiece& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } nfyVPwbvNF3FkNhxbB3/pw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
