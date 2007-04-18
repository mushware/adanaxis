//%includeGuardStart {
#ifndef MUSHMESH4VERTEXGENERATOR_H
#define MUSHMESH4VERTEXGENERATOR_H
//%includeGuardStart } aGXuKHsLx2kX/rNKSDwH/Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4VertexGenerator.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } i+fZc+YwTV1nx8X9k7EDdA
/*
 * $Id: MushMesh4VertexGenerator.h,v 1.2 2006/06/01 15:39:29 southa Exp $
 * $Log: MushMesh4VertexGenerator.h,v $
 * Revision 1.2  2006/06/01 15:39:29  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMeshStandard.h"

//:generate virtual standard ostream xml1
class MushMesh4VertexGenerator : public MushcoreVirtualObject
{
public:
    
private:

//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMesh4VertexGenerator& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } xiQSkg2EdeuSnJfJ4WxYgg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
