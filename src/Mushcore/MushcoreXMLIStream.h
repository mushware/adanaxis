//%includeGuardStart {
#ifndef MUSHCOREXMLISTREAM_H
#define MUSHCOREXMLISTREAM_H
//%includeGuardStart } 4GDI2rjRWblNFqvrMDV7ag
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLIStream.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } k0No7lYD7eN99xHKZPXcDg
/*
 * $Id: MushcoreXMLIStream.h,v 1.1 2003/09/21 11:46:10 southa Exp $
 * $Log: MushcoreXMLIStream.h,v $
 * Revision 1.1  2003/09/21 11:46:10  southa
 * XML input stream
 *
 */

#include "MushcoreStandard.h"
#include "MushcoreXMLStream.h"

class MushcoreXMLConsumer;

class MushcoreXMLIStream : public MushcoreXMLStream
{
public:
    explicit MushcoreXMLIStream(std::istream *inPStream);
    virtual ~MushcoreXMLIStream();

    std::istream& DataStreamGet(void) { return *m_pDataStream; }
    const std::string& TagNameGet(void) { return m_tagName; }

    void ObjectRead(MushcoreXMLConsumer& inObj);
    
    void Throw(const std::string& inMessage);
    
private:
    std::istream *m_pInputStream;
    std::istream *m_pDataStream;
    std::string m_tagName;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
