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
 * $Id: MushcoreXMLIStream.cpp,v 1.5 2003/09/22 19:40:36 southa Exp $
 * $Log: MushcoreXMLIStream.cpp,v $
 * Revision 1.5  2003/09/22 19:40:36  southa
 * XML I/O work
 *
 * Revision 1.4  2003/09/21 23:15:08  southa
 * XML input stream improvements
 *
 * Revision 1.3  2003/09/21 18:49:41  southa
 * XML input stream work
 *
 * Revision 1.2  2003/09/21 15:57:11  southa
 * XML autogenerator work
 *
 * Revision 1.1  2003/09/21 11:46:10  southa
 * XML input stream
 *
 */

#include "MushcoreXMLIStream.h"

#include "MushcoreFail.h"
#include "MushcoreSTL.h"
#include "MushcoreUtil.h"
#include "MushcoreXMLConsumer.h"

using namespace std;
using namespace Mushware;

MushcoreXMLIStream::MushcoreXMLIStream(std::istream& inStream) :
    m_inStream(inStream),
    m_contentStart(0),
    m_contentEnd(0),
    m_contentLineNum(0)
{
}

MushcoreXMLIStream::~MushcoreXMLIStream()
{
    // delete m_pStream;
}

void
MushcoreXMLIStream::ObjectRead(MushcoreXMLConsumer& inObj)
{
    do
    {
        string tagStr;
        U32 dataStartPos;

        while (dataStartPos = MushcoreUtil::TagGet(tagStr, m_contentStr, m_contentStart),
                dataStartPos == 0)
        {
            InputFetch();
        }
        m_tagName = tagStr.substr(0, tagStr.find(' '));
    
        string closingStr("</"+m_tagName+">");
        U32 dataEndPos;
    
        while (dataEndPos = m_contentStr.find(closingStr, dataStartPos),
               dataEndPos == string::npos)
        {
            InputFetch();
        }
            
        U32 sequenceEndPos = dataEndPos + closingStr.size();

        U32 contentEndStore = m_contentEnd;
        m_contentStart = dataStartPos;
        m_contentEnd = dataEndPos;

        inObj.AutoXMLDataProcess(*this);
 
        m_contentStart = sequenceEndPos;
        m_contentEnd = contentEndStore;
        
    } while (m_contentStart < m_contentEnd);
}

void
MushcoreXMLIStream::ObjectRead(U32& outU32)
{
    string dataStr = DataUntilTake(",)");
    istringstream dataStream(dataStr);
    if (!(dataStream >> outU32))
    {
        Throw("Read unsigned failed");
    }
}    

void
MushcoreXMLIStream::ObjectRead(U8& outU8)
{
    U32 tempValue;
    ObjectRead(tempValue);
    outU8 = tempValue;
}

void
MushcoreXMLIStream::ObjectRead(string& outStr)
{
    outStr = DataUntilTake(",)");
    outStr = MushcoreUtil::XMLMetaRemove(outStr);
}

void
MushcoreXMLIStream::InputFetch(void)
{
    if (m_inStream.eof())
    {
        Throw("Unexpected end of input");
    }
    
    string newStr;
    std::getline(m_inStream, newStr);
    
    if (m_inStream.bad())
    {
        Throw("Read failure");
    }

    m_contentStr += newStr;
    ++m_contentLineNum;
}

string
MushcoreXMLIStream::DataGet(void) const
{
    MUSHCOREASSERT(m_contentEnd >= m_contentStart);
    return m_contentStr.substr(m_contentStart, m_contentEnd - m_contentStart);
}

string
MushcoreXMLIStream::DataUntilTake(const string& inStr)
{
    MUSHCOREASSERT(m_contentEnd >= m_contentStart);

    string dataStr = DataGet();
    U32 endPos = dataStr.find_first_of(inStr);

    if (endPos == string::npos)
    {
        m_contentStart = m_contentEnd;
    }
    else
    {
        m_contentStart += endPos;
    }

    MUSHCOREASSERT(m_contentEnd >= m_contentStart);
    // cout << "Took until '" << dataStr.substr(0, endPos) << "'" << endl;
    return dataStr.substr(0, endPos);
}

U32
MushcoreXMLIStream::DataSizeGet(void) const
{
    MUSHCOREASSERT(m_contentEnd >= m_contentStart);
    return m_contentEnd - m_contentStart;
}

void
MushcoreXMLIStream::Throw(const string& inMessage) const
{
    ostringstream message;
    message << "XML parsing failure within '" << m_contentStr.substr(m_contentStart) << "' in element ending at line " << m_contentLineNum << ": " << inMessage;
    throw(MushcoreSyntaxFail(message.str()));
}
