//%includeGuardStart {
#ifndef MUSHSKINSINGULAR_H
#define MUSHSKINSINGULAR_H
//%includeGuardStart } Bi+Sl554bG8sYG45Xne7BQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinSingular.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Y7ivpqYx/B9gRbnFzfZsGw
/*
 * $Id: MushSkinSingular.h,v 1.1 2006/10/19 15:41:37 southa Exp $
 * $Log: MushSkinSingular.h,v $
 * Revision 1.1  2006/10/19 15:41:37  southa
 * Item handling
 *
 */

#include "MushSkinStandard.h"

//:generate virtual standard ostream xml1
class MushSkinSingular : public MushcoreVirtualObject
{
public:
    MushSkinSingular();
    
    virtual void DivideSize(Mushware::t2U32& outSizes, Mushware::U32 inNumFacets);
    virtual void TexCoordsGenerate(MushMesh4Mesh& ioMesh);
    
protected:
        
private:
        Mushware::tVal m_pullInRatio;
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
operator<<(std::ostream& ioOut, const MushSkinSingular& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } WEe+I3W8dV7HSp3jc6XGEw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
