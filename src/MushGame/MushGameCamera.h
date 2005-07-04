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
 * $Id: MushGameCamera.h,v 1.3 2005/06/29 11:11:15 southa Exp $
 * $Log: MushGameCamera.h,v $
 * Revision 1.3  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
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

#include "API/mushMushGL.h"
#include "API/mushMushMesh.h"

//:generate virtual standard ostream xml1
class MushGameCamera : public MushcoreVirtualObject
{
public:
    MushGameCamera();
    MushGameCamera(const MushGameCamera& inCamera)
    {
        // Deep copy
        m_post = inCamera.m_post;
        m_projection = inCamera.m_projection;
        if (inCamera.m_pTiedRef == NULL)
        {
            m_pTiedRef = NULL;
        }
        else
        {
            m_pTiedRef = dynamic_cast<MushGameRef *>(inCamera.m_pTiedRef->AutoClone());
            if (m_pTiedRef == NULL)
            {
                throw MushcoreDataFail(std::string("Clone failure: MushGameRef != ")+inCamera.m_pTiedRef->AutoName());
            }
        }
    }
    const MushGameCamera& operator=(const MushGameCamera& inCamera);
    
    virtual ~MushGameCamera();
    
    virtual void FromTiedObjectUpdate(void);
    virtual void TiedRefCopy(MushGameRef *inpRef);
    
private:
    MushMeshPosticity m_post; //:readwrite
    MushGLProjection m_projection; //:readwrite
    MushGameRef *m_pTiedRef;
    
//%classPrototypes {
public:
    const MushMeshPosticity& Post(void) const { return m_post; }
    void PostSet(const MushMeshPosticity& inValue) { m_post=inValue; }
    const MushGLProjection& Projection(void) const { return m_projection; }
    void ProjectionSet(const MushGLProjection& inValue) { m_projection=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 6Znngf6eU1lxCXv2olz8HA
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
