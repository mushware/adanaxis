//%includeGuardStart {
#ifndef MUSHMESHLIBRARYMAKER_H
#define MUSHMESHLIBRARYMAKER_H
//%includeGuardStart } e915XX05AKuccGFWsRbiLQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryMaker.h
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
//%Header } 5PSH6E4yNe1JI4fymTSD8g
/*
 * $Id: MushMeshLibraryMaker.h,v 1.3 2007/04/18 09:22:53 southa Exp $
 * $Log: MushMeshLibraryMaker.h,v $
 * Revision 1.3  2007/04/18 09:22:53  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/08/01 17:21:35  southa
 * River demo
 *
 * Revision 1.1  2006/06/14 18:45:49  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshLibraryStandard.h"

//:xml1base MushMesh4Maker
//:generate virtual standard ostream xml1
class MushMeshLibraryMaker : public MushMesh4Maker
{
public:
	virtual void Make(MushMesh4Mesh& ioMesh);

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
operator<<(std::ostream& ioOut, const MushMeshLibraryMaker& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 0N0brCtHEFgfkOM8saE7zQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
