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
 * $Id: MushcoreXMLIStream.cpp,v 1.7 2003/09/24 19:03:23 southa Exp $
 * $Log: MushcoreXMLIStream.cpp,v $
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

        while (dataStartPos = TagGet(tagStr, m_contentStr, m_contentStart),
               dataStartPos == 0)
        {
            // Can be optimised
            InputFetch();
        }

        if (tagStr.substr(0, 1) == "/")
        {
            // This is the end of the outer object
            m_contentStart = dataStartPos;
            break;
        }
        
        m_tagName = tagStr.substr(0, tagStr.find(' '));
        
        m_contentStart = dataStartPos;

        inObj.AutoXMLDataProcess(*this);

        string closingTagStr;
        // Consume and check the trailing tag
        while (dataStartPos = TagGet(closingTagStr, m_contentStr, m_contentStart),
               dataStartPos == 0)
        {
            // Can be optimised
            InputFetch();
        }
        if (closingTagStr != "/"+tagStr)
        {
            Throw("Unmatched tag: '"+tagStr+"' != '"+closingTagStr+"'");
        }
        m_contentStart = dataStartPos;     
    } while (1);
}

void
MushcoreXMLIStream::ObjectRead(U32& outU32)
{
    string dataStr = DataUntilTake(",)=<");
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
    if (ByteTake() != '"')
    {
        Throw("Bad first character in string");
    }

    outStr = DataUntilTake("\"");
    outStr = MushcoreUtil::XMLMetaRemove(outStr);

    ByteTake(); // Remove the quote
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
MushcoreXMLIStream::DataUntilTake(const string& inStr)
{
    U32 endPos;

    while (endPos = m_contentStr.find_first_of(inStr, m_contentStart), endPos == string::npos)
    {
        InputFetch();
    }

    string dataStr = m_contentStr.substr(m_contentStart, endPos - m_contentStart);
    
    m_contentStart = endPos;

    // cout << "Took '" << dataStr << "'" << endl;
    return dataStr;
}

U32
MushcoreXMLIStream::TagGet(string& outTag, const string& inStr, U32 inPos)
{
    U32 startPos = inStr.find('<', inPos);
    if (startPos == string::npos) return 0;
    U32 endPos = inStr.find('>', startPos);
    if (endPos == string::npos)
    {
        Throw("Unclosed tag");
    }
    // change to use substr
    outTag = string(inStr, startPos+1, endPos-startPos-1);
    return endPos + 1;
}

void
MushcoreXMLIStream::Throw(const string& inMessage) const
{
    ostringstream message;
    message << "XML parsing failure within '" << m_contentStr.substr(m_contentStart) << "' in element ending at line " << m_contentLineNum << ": " << inMessage;
    throw(MushcoreSyntaxFail(message.str()));
}
