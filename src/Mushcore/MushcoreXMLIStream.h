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
 * $Id: MushcoreXMLIStream.h,v 1.12 2003/10/02 23:33:39 southa Exp $
 * $Log: MushcoreXMLIStream.h,v $
 * Revision 1.12  2003/10/02 23:33:39  southa
 * XML polymorphic objects
 *
 * Revision 1.11  2003/09/30 22:11:30  southa
 * XML objects within objects
 *
 * Revision 1.10  2003/09/29 21:48:37  southa
 * XML work
 *
 * Revision 1.9  2003/09/27 17:50:49  southa
 * XML null pointer handling
 *
 * Revision 1.8  2003/09/25 20:02:25  southa
 * XML pointer work
 *
 * Revision 1.7  2003/09/24 19:03:23  southa
 * XML map IO
 *
 * Revision 1.6  2003/09/23 22:57:57  southa
 * XML vector handling
 *
 * Revision 1.5  2003/09/22 19:40:36  southa
 * XML I/O work
 *
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
#include "MushcoreUtil.h"

class MushcoreVirtualObject;

class MushcoreXMLIStream : public MushcoreXMLStream
{
public:
    explicit MushcoreXMLIStream(std::istream& inPStream);
    virtual ~MushcoreXMLIStream();

    std::string DataUntilTake(const std::string& inStr);
    const std::string& TagNameGet(void) const { return m_tagName; }

    template<class T> void ObjectRead(T *& inpObj);
    template<class T> void ObjectRead(std::vector<T>& inVector);
    template<class T> void ObjectRead(std::vector<T *>& inVector);
    template<class T, class U> void ObjectRead(std::map<T, U>& inMap);

    void ObjectRead(MushcoreVirtualObject *inpObj);
    void ObjectRead(MushcoreVirtualObject& inObj);

    void ObjectRead(Mushware::U32& outU32);
    void ObjectRead(Mushware::U8& outU8);
    void ObjectRead(std::string& outStr);

    void Throw(const std::string& inMessage) const;
    
protected:
    Mushware::U8 ByteGet(void);
    Mushware::U8 ByteTake(void);
    Mushware::U32 TagGet(std::string& outTag, const std::string& inStr, Mushware::U32 inPos = 0);
    const std::string& TagDataGet(void) const { return m_tagData; }
    
    void InputFetch(void);

private:    
    std::istream& m_inStream;
    std::string m_tagName;
    std::string m_contentStr;
    std::string m_indentStr;
    std::string m_tagData;
    Mushware::U32 m_contentStart;
    Mushware::U32 m_contentLineNum;
};

inline Mushware::U8
MushcoreXMLIStream::ByteGet(void)
{
    if (m_contentStart >= m_contentStr.size())
    {
        InputFetch();
    }
    return m_contentStr[m_contentStart];
}

inline Mushware::U8
MushcoreXMLIStream::ByteTake(void)
{
    if (m_contentStart >= m_contentStr.size())
    {
        InputFetch();
    }
    // cout << "took '" << m_contentStr[m_contentStart] << "'" << endl;
    return m_contentStr[m_contentStart++];
}

template<class T>
inline void
operator>>(MushcoreXMLIStream& ioIn, T& inObj)
{
    ioIn.ObjectRead(inObj);
}

inline void
operator>>(MushcoreXMLIStream& ioIn, MushcoreVirtualObject *& inObj)
{
    ioIn.ObjectRead(inObj);
}

template<class T>
inline void
MushcoreXMLIStream::ObjectRead(T *& inpObj)
{
    if (m_contentStr.substr(m_contentStart, 4) == "NULL")
    {
        inpObj = NULL;
        m_contentStart += 4;;
    }
    else
    {
        if (inpObj == NULL)
        {
            inpObj = new T;
        }
        *this >> *inpObj;
    }
}

template<class T>
inline void
MushcoreXMLIStream::ObjectRead(vector<T>& inVector)
{
    // Decode the (x,y,z) sequence

    if (ByteTake() != '(')
    {
        Throw("Bad first character in vector");
    }

    if (ByteGet() == ')')
    {
        // Consume the end marker
        ByteTake();
    }
    else
    {
        for (;;)
        {
            inVector.push_back();
            try
            {
                *this >> inVector.back();
            }
            catch (...)
            {
                // Remove partially written object
                inVector.pop_back();
                throw;
            }
            
            Mushware::U8 nextByte = ByteTake();
            if (nextByte == ',')
            {
            }
            else if (nextByte == ')')
            {
                return;
            }
            else
            {
                Throw("Bad delimiter in vector");
            }
        }
    }
}

template<class T>
inline void
MushcoreXMLIStream::ObjectRead(vector<T *>& inVector)
{
    // Decode the (x,y,z) sequence

    if (ByteTake() != '(')
    {
        Throw("Bad first character in vector");
    }

    if (ByteGet() == ')')
    {
        // Consume the end marker
        ByteTake();
    }
    else
    {
        for (;;)
        {
            T *newPtr = NULL;
            *this >> newPtr;
            inVector.push_back(newPtr);

            Mushware::U8 nextByte = ByteTake();
            if (nextByte == ',')
            {
            }
            else if (nextByte == ')')
            {
                return;
            }
            else
            {
                Throw("Bad delimiter in vector");
            }
        }
    }
}



template<class T, class U>
inline void
MushcoreXMLIStream::ObjectRead(map<T, U>& inMap)
{
    // Decode the (x,y,z) sequence

    if (ByteTake() != '(')
    {
        Throw("Bad first character in map");
    }

    if (ByteGet() == ')')
    {
        // Consume the end marker
        ByteTake();
    }
    else
    {
        for (;;)
        {
            T keyValue;
            ObjectRead(keyValue);

            if (ByteTake() != '=')
            {
                Throw("Bad separator in map");
            }

            // Read completely before setting the map, in case of exception
            U valueValue;
            ObjectRead(valueValue);
            inMap[keyValue] = valueValue;
            
            Mushware::U8 nextByte = ByteTake();
            if (nextByte == ',')
            {
            }
            else if (nextByte == ')')
            {
                return;
            }
            else
            {
                Throw("Bad delimiter in vector");
            }
        }
    }
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
