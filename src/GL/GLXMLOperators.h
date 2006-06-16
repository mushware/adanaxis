//%includeGuardStart {
#ifndef GLXMLOPERATORS_H
#define GLXMLOPERATORS_H
//%includeGuardStart } VmHinfJK7FiML780R1+NgA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLXMLOperators.h
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
//%Header } vGQlymfouKr/B/ABxXbF2g
/*
 * $Id: GLXMLOperators.h,v 1.6 2006/06/01 15:38:55 southa Exp $
 * $Log: GLXMLOperators.h,v $
 * Revision 1.6  2006/06/01 15:38:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.4  2005/03/30 23:33:56  southa
 * win32 and gcc 2.95 fixes
 *
 * Revision 1.3  2005/02/03 21:02:52  southa
 * Build fixes
 *
 * Revision 1.2  2004/09/27 22:42:08  southa
 * MSVC compilation fixes
 *
 * Revision 1.1  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 */

#include "GLStandard.h"

#if 0

inline void
operator>>(MushcoreXMLIStream& ioIn, GLenum& outObj)
{
    Mushware::tXMLVal xmlVal;
    ioIn.ObjectRead(xmlVal);
    outObj = static_cast<GLenum>(xmlVal);
}

#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
