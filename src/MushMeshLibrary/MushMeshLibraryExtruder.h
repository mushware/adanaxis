//%includeGuardStart {
#ifndef MUSHMESHLIBRARYEXTRUDER_H
#define MUSHMESHLIBRARYEXTRUDER_H
//%includeGuardStart } lws/dPz9JE8RT5RK2La+iQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryExtruder.h
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
//%Header } FoGgastGYAMxM1mWOde9Ag
/*
 * $Id: MushMeshLibraryExtruder.h,v 1.3 2007/04/18 09:22:53 southa Exp $
 * $Log: MushMeshLibraryExtruder.h,v $
 * Revision 1.3  2007/04/18 09:22:53  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/08/01 17:21:34  southa
 * River demo
 *
 * Revision 1.1  2006/06/14 11:20:08  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshLibraryStandard.h"

//:xml1base MushMesh4Extruder
//:generate virtual standard ostream xml1
class MushMeshLibraryExtruder : public MushMesh4Extruder
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
operator<<(std::ostream& ioOut, const MushMeshLibraryExtruder& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Yavkbwn2xz713XzxiAacEA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
