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
 * $Id: MushcoreXMLIStream.h,v 1.4 2003/09/21 23:15:08 southa Exp $
 * $Log: MushcoreXMLIStream.h,v $
 * Revision 1.4  2003/09/21 23:15:08  southa
 * XML input stream improvements
 *
 * Revision 1.3  2003/09/21 18:49:41  southa
 * XML input stream work
 *
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
    explicit MushcoreXMLIStream(std::istream& inPStream);
    virtual ~MushcoreXMLIStream();

    std::string DataGet(void) const;
    const std::string& TagNameGet(void) const { return m_tagName; }

    void ObjectRead(MushcoreXMLConsumer& inObj);
    void ObjectRead(Mushware::U32& outU32);
    void ObjectRead(Mushware::U8& outU8);
    void ObjectRead(std::string& outStr);

protected:
    void Throw(const std::string& inMessage);
    void InputFetch(void);

private:    
    std::istream& m_inStream;
    std::string m_tagName;
    std::string m_contentStr;
    Mushware::U32 m_contentStart;
    Mushware::U32 m_contentEnd;
    Mushware::U32 m_contentLineNum;
};

template<class T>
inline void
operator>>(MushcoreXMLIStream& ioIn, T& inObj)
{
    ioIn.ObjectRead(inObj);
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
