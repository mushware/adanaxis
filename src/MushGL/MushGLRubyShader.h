//%includeGuardStart {
#ifndef MUSHGLRUBYSHADER_H
#define MUSHGLRUBYSHADER_H
//%includeGuardStart } WwbZBL15DrZVigx4xjmeCg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLRubyShader.h
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
//%Header } uvOdj7JHTp+sQX4yst5P7Q
/*
 * $Id$
 * $Log$
 */

#include "MushGLStandard.h"

#include "MushGLShader.h"

#include "API/mushMushRuby.h"

class MushGLRubyShader : public MushRubyDataObj<MushGLShader>
{
public:
    static Mushware::tRubyValue Dump(Mushware::tRubyValue inSelf);

private:
};

MUSHRUBYDATAOBJ_INSTALL(MushGLShader)(void)
{
	DataObjInstall("MushGLShader");
    MushRubyUtil::MethodDefineNoParams(Klass(), "mDump", MushGLRubyShader::Dump);
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
