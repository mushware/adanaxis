//%includeGuardStart {
#ifndef MUSHRENDERSPEC_H
#define MUSHRENDERSPEC_H
//%includeGuardStart } MUbKk7V90INvJGmjmfoblQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderSpec.h
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
//%Header } hzHOaqG45RxILxoV7rJ+JA
/*
 * $Id: MushRenderSpec.h,v 1.2 2005/07/01 16:42:54 southa Exp $
 * $Log: MushRenderSpec.h,v $
 * Revision 1.2  2005/07/01 16:42:54  southa
 * Render work
 *
 * Revision 1.1  2005/07/01 10:36:46  southa
 * MushRender work
 *
 */

#include "MushRenderStandard.h"

#include "MushRenderSpec.h"

#include "API/mushMushGL.h"

//:generate standard ostream xml1
class MushRenderSpec : MushcoreVirtualObject
{
public:
    virtual ~MushRenderSpec() {}
    
    // const MushGLModelView& ModelToClipMatress() const;
    
private:
    MushGLProjection m_projection; //:readwrite
    // MushGLModelView m_model;
    // MushGLModelView m_view;
    // MushGLModelView m_model;

    
//%classPrototypes {
public:
    const MushGLProjection& Projection(void) const { return m_projection; }
    void ProjectionSet(const MushGLProjection& inValue) { m_projection=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Q5OIIIyHT4uiimE+u/KsZg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushRenderSpec& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } AwM/RwQovTTCL3UpRXcpCg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
