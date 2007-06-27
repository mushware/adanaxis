//%includeGuardStart {
#ifndef MUSHSKINTILED_H
#define MUSHSKINTILED_H
//%includeGuardStart } kZD0CEqivw3yeKDiSUrmlA
//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinTiled.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.4, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } nvBxKiVkdneXWo5JPiCymQ
/*
 * $Id: MushSkinTiled.h,v 1.4 2007/04/18 09:23:05 southa Exp $
 * $Log: MushSkinTiled.h,v $
 * Revision 1.4  2007/04/18 09:23:05  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/08/01 17:21:41  southa
 * River demo
 *
 * Revision 1.2  2006/06/09 21:07:15  southa
 * Tiled skin generation
 *
 * Revision 1.1  2006/06/07 12:15:22  southa
 * Grid and test textures
 *
 * Revision 1.2  2006/06/01 15:39:40  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/08/29 18:40:57  southa
 * Solid rendering work
 *
 */

#include "MushSkinStandard.h"

//:generate virtual standard ostream xml1
class MushSkinTiled : public MushcoreVirtualObject
{
public:
    MushSkinTiled();
    
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
operator<<(std::ostream& ioOut, const MushSkinTiled& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } G5CINZQknhQNvC3mkG1rWg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
