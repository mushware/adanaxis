//%includeGuardStart {
#ifndef MUSHMESHRUBYMESH_H
#define MUSHMESHRUBYMESH_H
//%includeGuardStart } 0fz+h5HaFSFoFE3/de8MLg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyMesh.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } hSrHx4/wCdfB19VcRmiYhw
/*
 * $Id$
 * $Log$
 */

#include "MushMeshRubyStandard.h"

class MushMeshMesh;

class MushMeshRubyMesh
{
public:
	typedef MushMesh4Mesh tBase;
	typedef MushcoreDataRef<tBase> tContainer;
	
	static void RubyInstall(void);
	
	static tBase& Ref(Mushware::tRubyValue inSelf);
	
private:
	static Mushware::tRubyValue MushMeshAllocate(Mushware::tRubyValue inKlass);
	static void MushMeshFree(void *inPtr);			
	static tContainer& ContainerObj(Mushware::tRubyValue inSelf);
	static tBase& RefObj(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue MushMeshInitialize(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue MushMeshInitializeCopy(Mushware::tRubyValue inCopy, Mushware::tRubyValue inOrig);
	static Mushware::tRubyValue MushMesh_to_s(Mushware::tRubyValue inSelf);

	static Mushware::tRubyValue m_meshKlass;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
