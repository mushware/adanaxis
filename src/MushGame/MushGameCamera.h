//%includeGuardStart {
#ifndef MUSHGAMECAMERA_H
#define MUSHGAMECAMERA_H
//%includeGuardStart } tzdeCLD2iutbzAqx4mj2vw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameCamera.h
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
//%Header } iR1nzzDghU7XG/JS99oDQQ
/*
 * $Id: MushGameCamera.h,v 1.2 2005/06/29 09:07:56 southa Exp $
 * $Log: MushGameCamera.h,v $
 * Revision 1.2  2005/06/29 09:07:56  southa
 * MushGame camera work
 *
 * Revision 1.1  2005/06/24 10:30:12  southa
 * MushGame camera work
 *
 */

#include "MushGameStandard.h"

#include "MushGamePiece.h"
#include "MushGamePlayer.h"
#include "MushGameRef.h"

#include "API/mushMushMesh.h"

//:generate virtual standard ostream xml1
class MushGameCamera : public MushcoreVirtualObject
{
public:
    MushGameCamera();
    virtual ~MushGameCamera();
    
    virtual void FromTiedObjectUpdate(void);
    virtual void TiedRefCopy(MushGameRef *inpRef);
    
private:
    MushMeshPosticity m_post; //:readwrite
    MushGameRef *m_pTiedRef;
    
//%classPrototypes {
public:
    const MushMeshPosticity& Post(void) const { return m_post; }
    void PostSet(const MushMeshPosticity& inValue) { m_post=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } bYrWlL9gkU9u2rKZSes7wA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameCamera& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } yEL8lWokyDIR1M7RFn0mFw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
