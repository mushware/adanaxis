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
 * $Id: MushcoreXMLIStream.h,v 1.2 2003/09/21 15:57:12 southa Exp $
 * $Log: MushcoreXMLIStream.h,v $
 * Revision 1.2  2003/09/21 15:57:12  southa
 * XML autogenerator work
 *
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

    std::string DataGet(void) const;
    std::istream *TempIStreamNew(void) const;
    const std::string& TagNameGet(void) const { return m_tagName; }

    void ObjectRead(MushcoreXMLConsumer& inObj);
    
    void Throw(const std::string& inMessage);
    
private:
    void InputFetch(void);
    
    std::istream *m_pInputStream;
    std::string m_tagName;
    std::string m_contentStr;
    Mushware::U32 m_contentStart;
    Mushware::U32 m_contentEnd;
    Mushware::U32 m_contentLineNum;
};

template<class T>
inline MushcoreXMLIStream&
operator>>(MushcoreXMLIStream& ioIn, T& inObj)
{
    std::istream *pIStream = ioIn.TempIStreamNew();

    *pIStream >> inObj;
    
    delete pIStream;
    return ioIn;
}


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
