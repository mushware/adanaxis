//%includeGuardStart {
#ifndef MUSHMESHRUBYBASE_H
#define MUSHMESHRUBYBASE_H
//%includeGuardStart } 9MiiRzYXUcDq4xuXNoK2NQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyBase.h
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
//%Header } qiS55gKJz6aDLc2hHzgzYg
/*
 * $Id: MushMeshRubyBase.h,v 1.2 2006/07/07 07:57:29 southa Exp $
 * $Log: MushMeshRubyBase.h,v $
 * Revision 1.2  2006/07/07 07:57:29  southa
 * Key translation
 *
 * Revision 1.1  2006/06/16 12:11:04  southa
 * Ruby subclasses
 *
 */

#include "MushMeshRubyStandard.h"

class MushMeshRubyBase : public MushRubyEmptyObj<1000>
{
public:
private:
};

MUSHRUBYEMPTYOBJ_INSTALL(1000)(void)
{
	EmptyInstall("MushBase");
    
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
