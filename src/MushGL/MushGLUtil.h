//%includeGuardStart {
#ifndef MUSHGLUTIL_H
#define MUSHGLUTIL_H
//%includeGuardStart } rAQ4jcchYa85P6BeLBYvlA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLUtil.h
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
//%Header } mloCIUiyLTpzM0as6xBKwg
/*
 * $Id$
 * $Log$
 */

#include "API/mushMushMesh.h"

#include "MushGLAppHandler.h"

class MushGLUtil
{
public:
    static void IdentityPrologue(void);
    static void IdentityEpilogue(void);
    static void OrthoPrologue(void);
    static void OrthoEpilogue(void);
    static void DisplayPrologue(void);
    static void DisplayEpilogue(void);
    static void ClearScreen(void);
    static MushGLAppHandler& AppHandler(void);
    
    static const Mushware::t2Val ScreenSize(void);
    static const Mushware::t2Val ScreenRatios(void);

    static Mushware::tVal LongestScreenAxis(void);
    static Mushware::tVal ScreenAspectRatio(void);

private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
