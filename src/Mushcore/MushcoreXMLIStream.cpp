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
 * $Id: MushcoreXMLIStream.cpp,v 1.3 2003/09/21 18:49:41 southa Exp $
 * $Log: MushcoreXMLIStream.cpp,v $
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

MushcoreXMLIStream::MushcoreXMLIStream(std::istream *inPStream) :
    m_pInputStream(inPStream),
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
    istringstream inStream(DataGet());
    if (!(inStream >> outU32))
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
MushcoreXMLIStream::InputFetch(void)
{
    if (m_pInputStream->eof())
    {
        Throw("Unexpected end of input");
    }
    
    string newStr;
    std::getline(*m_pInputStream, newStr);
    
    if (m_pInputStream->bad())
    {
        Throw("Read failure");
    }

    m_contentStr += newStr;
    ++m_contentLineNum;
}

std::string
MushcoreXMLIStream::DataGet(void) const
{
    return m_contentStr.substr(m_contentStart, m_contentEnd - m_contentStart);
}

void
MushcoreXMLIStream::Throw(const string& inMessage)
{
    ostringstream message;
    message << "XML parsing failure within '" << m_contentStr.substr(m_contentStart) << "' at line " << m_contentLineNum << ": " << inMessage;
    throw(MushcoreSyntaxFail(message.str()));
}
