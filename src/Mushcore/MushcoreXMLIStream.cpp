//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLIStream.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } TQc+Pef4I2KQ3HNa4YFM4A
/*
 * $Id: MushcoreXMLIStream.cpp,v 1.11 2003/10/03 23:39:34 southa Exp $
 * $Log: MushcoreXMLIStream.cpp,v $
 * Revision 1.11  2003/10/03 23:39:34  southa
 * XML polymorphs
 *
 * Revision 1.10  2003/10/02 23:33:39  southa
 * XML polymorphic objects
 *
 * Revision 1.9  2003/09/30 22:11:30  southa
 * XML objects within objects
 *
 * Revision 1.8  2003/09/29 21:48:37  southa
 * XML work
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
 * Revision 1.2  2003/09/21 15:57:11  southa
 * XML autogenerator work
 *
 * Revision 1.1  2003/09/21 11:46:10  southa
 * XML input stream
 *
 */

#include "MushcoreXMLIStream.h"

#include "MushcoreFactory.h"
#include "MushcoreFail.h"
#include "MushcoreSTL.h"
#include "MushcoreUtil.h"
#include "MushcoreVirtualObject.h"

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
}

void
MushcoreXMLIStream::ObjectRead(MushcoreVirtualObject *outpObj)
{
    string tagStr;
    do
    {
        U32 dataStartPos;

        while (dataStartPos = TagGet(tagStr, m_contentStr, m_contentStart),
               dataStartPos == 0)
        {
            // Can be optimised
            InputFetch();
        }

        if (tagStr.substr(0, 1) == "/")
        {
            // cout << "Break on '" << m_contentStr.substr(m_contentStart, dataStartPos-m_contentStart) << "'" << endl;
            // This is the end of the outer object
            // m_contentStart = dataStartPos;
            break;
        }
        // Store tag data for attributes
        if (tagStr.find(' ') != string::npos)
        {
            // Not sure about this - preserves types from way back
            m_tagData = tagStr;
        }
        tagStr = tagStr.substr(0, tagStr.find(' '));
        
        m_contentStart = dataStartPos;
        // Tag is read and m_contentStart points to the start of the tag data

        if (outpObj == NULL)
        {
            /* Pointer is NULL, so this is a pointer to a polymorphic type
             * which we might need to allocate
            */
            if (m_contentStr.substr(m_contentStart, 4) == "NULL")
            {
                outpObj = NULL;
                m_contentStart += 4;;
            }
            else
            {
                string typeStr;
                if (!MushcoreUtil::XMLAttributeExtract(typeStr, TagDataGet(), "type"))
                {
                    // No type specified, so cannot create object


                    Throw("No type= attribute for polymorphic object '"+TagDataGet()+"'");
                }
                if (outpObj != NULL)
                {
                    delete outpObj;
                }
                
                outpObj = dynamic_cast<MushcoreVirtualObject *>(MushcoreFactory::Sgl().ObjectCreate(typeStr));

                if (outpObj == NULL)
                {
                    // Dynamic cast failed
                    Throw("Object of type "+typeStr+" not virtual enough");
                }
            }
            
        }

        if (outpObj != NULL)
        {
            // cout << m_indentStr << "Threading " << tagStr << endl; m_indentStr += " ";
            outpObj->AutoXMLDataProcess(*this, tagStr);
            // m_indentStr = m_indentStr.substr(0, m_indentStr.size()-1); cout << m_indentStr << "Unthreading " << tagStr << endl;
        }
        
        string closingTagStr;
        // Consume and check the trailing tag
        while (dataStartPos = TagGet(closingTagStr, m_contentStr, m_contentStart),
               dataStartPos == 0)
        {
            // Can be optimised
            InputFetch();
        }
        // cout << "Skipped '" << m_contentStr.substr(m_contentStart, dataStartPos-m_contentStart) << "'" << endl;
        if (closingTagStr != "/"+tagStr)
        {
            Throw("Unmatched tag: Found '"+closingTagStr+"', expected '/"+tagStr+"'");
        }

        m_contentStart = dataStartPos;     
    } while (tagStr != "obj");
}


void
MushcoreXMLIStream::ObjectRead(MushcoreVirtualObject& outObj)
{
    ObjectRead(&outObj);
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
MushcoreXMLIStream::ObjectRead(tVal& outObj)
{
    string dataStr = DataUntilTake(",)=<");
    istringstream dataStream(dataStr);
    if (!(dataStream >> outObj))
    {
        Throw("Read tVal failed");
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

    // if m_contentStart == m_contentStr.size() {m_contentStr.erase(); m_contentStart=0}
    
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

// Returns the length of tag found
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
