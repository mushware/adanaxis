//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLIStream.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } YEOo+pXU/aO2Yxoi77dW6A
/*
 * $Id$
 * $Log$
 */

#include "MushcoreXMLIStream.h"

#include "MushcoreFail.h"
#include "MushcoreSTL.h"

using namespace std;
using namespace Mushware;

MushcoreXMLIStream::MushcoreXMLIStream(std::istream *inPStream)
{
    m_pStream = inPStream;
}

MushcoreXMLIStream::~MushcoreXMLIStream()
{
    // delete m_pStream;
}

bool
MushcoreXMLIStream::LineAvailable(void)
{
    return !m_pStream->eof();
}        

const string&
MushcoreXMLIStream::LineTake(void)
{
    if (m_pStream->eof())
    {
        Throw("Read on empty stream");
    }
    std::getline(*m_pStream, m_currentLine);
    if (m_pStream->bad())
    {
        Throw("Read failure");
    }
    
    return m_currentLine;
}

void
MushcoreXMLIStream::Throw(const string& inMessage)
{
    ostringstream message;
    message << "XML parsing failure in '" << m_currentLine << "'";
    throw(MushcoreSyntaxFail(message.str()));
}
