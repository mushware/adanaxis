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
 * $Id$
 * $Log$
 */

#include "MushcoreStandard.h"
#include "MushcoreXMLStream.h"

class MushcoreXMLIStream : public MushcoreXMLStream
{
public:
    explicit MushcoreXMLIStream(std::istream *inPStream);
    virtual ~MushcoreXMLIStream();

    std::istream& IStreamGet() { return *m_pStream; }
    bool LineAvailable(void);
    const std::string& LineTake(void);
    
    void Throw(const std::string& inMessage);
    
private:
    std::istream *m_pStream;
    std::string m_currentLine;
};

template<class T>
inline MushcoreXMLIStream&
operator>>(MushcoreXMLIStream& ioIn, T& inObj)
{
    ioIn.IStreamGet() >> inObj;
    return ioIn;
}

inline bool
operator!(MushcoreXMLIStream& ioIn)
{
    return !ioIn.IStreamGet();
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
