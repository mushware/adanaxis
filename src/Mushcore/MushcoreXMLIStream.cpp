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
 * $Id: MushcoreXMLIStream.cpp,v 1.1 2003/09/21 11:46:10 southa Exp $
 * $Log: MushcoreXMLIStream.cpp,v $
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

MushcoreXMLIStream::MushcoreXMLIStream(std::istream *inPStream)
{
    m_pInputStream = inPStream;
    m_pDataStream = NULL;
}

MushcoreXMLIStream::~MushcoreXMLIStream()
{
    // delete m_pStream;
}

void
MushcoreXMLIStream::ObjectRead(MushcoreXMLConsumer& inObj)
{
    string contentStr;
    while (!m_pInputStream->eof())
    {
        string newStr;
        std::getline(*m_pInputStream, newStr);
        if (m_pInputStream->bad())
        {
            Throw("Read failure");
        }
        
        contentStr += newStr;
        
        while (1)
        {
            string tagStr;
            U32 dataStartPos = MushcoreUtil::TagGet(tagStr, contentStr);
            if (dataStartPos == 0)
            {
                break; // No tag - get more input
            }
            
            m_tagName = tagStr.substr(0, tagStr.find(' '));

            string closingStr("</"+m_tagName+">");
            U32 dataEndPos = contentStr.find(closingStr, dataStartPos);
            U32 sequenceEndPos = dataEndPos + closingStr.size();
            if (dataEndPos == string::npos)
            {
                break; // Need more input
            }
            istringstream dataStream(contentStr.substr(dataStartPos, dataEndPos - dataStartPos)); // FIXME: efficiency

            m_pDataStream = &dataStream;
            inObj.XMLDataProcess(*this);
            m_pDataStream = NULL;

            contentStr = contentStr.substr(sequenceEndPos, string::npos); // FIXME: efficiency
        }
    }
}

void
MushcoreXMLIStream::Throw(const string& inMessage)
{
    ostringstream message;
    message << "XML parsing failure in '" << "'";
    throw(MushcoreSyntaxFail(message.str()));
}
