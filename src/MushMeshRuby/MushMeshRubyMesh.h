//%includeGuardStart {
#ifndef MUSHMESHRUBYMESH_H
#define MUSHMESHRUBYMESH_H
//%includeGuardStart } 0fz+h5HaFSFoFE3/de8MLg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyMesh.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } j054oTBCmtmw2r6J08cSSQ
/*
 * $Id: MushMeshRubyMesh.h,v 1.9 2006/11/14 14:02:17 southa Exp $
 * $Log: MushMeshRubyMesh.h,v $
 * Revision 1.9  2006/11/14 14:02:17  southa
 * Ball projectiles
 *
 * Revision 1.8  2006/07/17 14:43:41  southa
 * Billboarded deco objects
 *
 * Revision 1.7  2006/06/19 15:57:19  southa
 * Materials
 *
 * Revision 1.6  2006/06/16 01:02:33  southa
 * Ruby mesh generation
 *
 * Revision 1.5  2006/06/14 18:45:49  southa
 * Ruby mesh generation
 *
 * Revision 1.4  2006/06/14 11:20:08  southa
 * Ruby mesh generation
 *
 * Revision 1.3  2006/06/13 19:30:37  southa
 * Ruby mesh generation
 *
 * Revision 1.2  2006/06/13 10:35:04  southa
 * Ruby data objects
 *
 * Revision 1.1  2006/06/12 16:01:23  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshRubyStandard.h"

class MushMeshMesh;

class MushMeshRubyMesh : public MushRubyDataObj<MushMesh4Mesh>
{
public:
	static void RubyInstall(void);
	
protected:
	static Mushware::tRubyValue BaseAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue BaseDisplacementAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue BillboardSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue BillboardRandomSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue ExtruderAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue MaterialAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
	static Mushware::tRubyValue Make(Mushware::tRubyValue inSelf);

private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
