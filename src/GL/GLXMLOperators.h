//%includeGuardStart {
#ifndef GLXMLOPERATORS_H
#define GLXMLOPERATORS_H
//%includeGuardStart } VmHinfJK7FiML780R1+NgA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLXMLOperators.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 4oyuaAIZhw3W7rwbERri6A
/*
 * $Id: GLXMLOperators.h,v 1.2 2004/09/27 22:42:08 southa Exp $
 * $Log: GLXMLOperators.h,v $
 * Revision 1.2  2004/09/27 22:42:08  southa
 * MSVC compilation fixes
 *
 * Revision 1.1  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 */

#include "GLStandard.h"

inline void
operator>>(MushcoreXMLIStream& ioIn, GLenum& outObj)
{
    Mushware::tXMLVal xmlVal;
    ioIn.ObjectRead(xmlVal);
    outObj = static_cast<GLenum>(xmlVal);
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
