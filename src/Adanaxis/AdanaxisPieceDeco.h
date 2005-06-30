//%includeGuardStart {
#ifndef ADANAXISPIECEDECO_H
#define ADANAXISPIECEDECO_H
//%includeGuardStart } oqn4Y6tbxdOzvAL0fqtoXA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceDeco.h
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
//%Header } enJUO8WAIa4qUMI3BXYVJA
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisStandard.h"

#include "API/mushMushGame.h"
#include "API/mushMushMesh.h"

//:xml1base MushGamePiece
//:generate virtual standard ostream xml1
class AdanaxisPieceDeco : public MushGamePiece
{
public:
    explicit AdanaxisPieceDeco(const std::string& inID = 0);
    virtual ~AdanaxisPieceDeco() {}
    
    virtual void Render(MushGameLogic& ioLogic, const MushGameCamera& inCamera);
    
private:
    std::string m_id;
    MushMesh4Mesh m_mesh; //:readwrite
    
//%classPrototypes {
public:
    const MushMesh4Mesh& Mesh(void) const { return m_mesh; }
    void MeshSet(const MushMesh4Mesh& inValue) { m_mesh=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } r3k1iP3VZ2PsVPp0+7UJNA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisPieceDeco& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } U59qcX7inEXnV9haw5/Q8Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
