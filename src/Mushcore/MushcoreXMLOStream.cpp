//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLOstream.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } nJdVJ8jiSMikKV4dE2rJkw
/*
 * $Id$
 * $Log$
 */

#include "MushcoreXMLOstream.h"

#include "MushcoreSTL.h"
MushcoreXMLOStream::MushcoreXMLOStream()
{
    m_pStream = new std::ostringstream;
}

MushcoreXMLOStream::~MushcoreXMLOStream()
{
    delete m_pStream;
}

void
MushcoreXMLOStream::Print(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "*m_pStream=" << dynamic_cast<std::ostringstream *>(m_pStream)->str();
    ioOut << "]";
}
