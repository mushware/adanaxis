//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreVirtualObject.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } CI/MB1YAZZBxkJaEWhlKSw
/*
 * $Id: MushcoreVirtualObject.cpp,v 1.2 2004/01/02 21:13:14 southa Exp $
 * $Log: MushcoreVirtualObject.cpp,v $
 * Revision 1.2  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/02 23:33:38  southa
 * XML polymorphic objects
 *
 */

#include "MushcoreVirtualObject.h"

void
MushcoreVirtualObject::AutoInputPrologue(MushcoreXMLIStream& ioIn)
{
    // Do nothing in default prologue
}

void
MushcoreVirtualObject::AutoInputEpilogue(MushcoreXMLIStream& ioIn)
{
    // Do nothing in default epilogue
}

void
MushcoreVirtualObject::AutoOutputPrologue(MushcoreXMLOStream& ioOut) const
{
    // Do nothing in default prologue
}

void
MushcoreVirtualObject::AutoOutputEpilogue(MushcoreXMLOStream& ioOut) const
{
    // Do nothing in default epilogue
}
