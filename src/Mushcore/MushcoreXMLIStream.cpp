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
 * $Id: MushcoreXMLIStream.cpp,v 1.20 2005/03/25 19:13:50 southa Exp $
 * $Log: MushcoreXMLIStream.cpp,v $
 * Revision 1.20  2005/03/25 19:13:50  southa
 * GameDialogue work
 *
 * Revision 1.19  2005/02/10 12:34:19  southa
 * Template fixes
 *
 * Revision 1.18  2004/09/26 19:42:05  southa
 * Added MushMesh, fixed typenames and release target
 *
 * Revision 1.17  2004/01/18 18:25:29  southa
 * XML stream upgrades
 *
 * Revision 1.16  2004/01/08 22:41:10  southa
 * MushModel commands
 *
 * Revision 1.15  2004/01/08 16:06:11  southa
 * XML fixes
 *
 * Revision 1.14  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.13  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.12  2004/01/02 17:31:48  southa
 * MushPie work and XML fixes
 *
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

// #define MUSHCORE_XMLITESTING

#ifdef MUSHCORE_XMLITESTING
#define MUSHCOREXMLISTREAM_DEBUG(a) a
#else
#define MUSHCOREXMLISTREAM_DEBUG(a)
#endif

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
MushcoreXMLIStream::ObjectReadVirtual(MushcoreVirtualObject *& outpObj)
{
    MUSHCOREXMLISTREAM_DEBUG((cout << m_indentStr << "Entering" << endl));
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
            MUSHCOREXMLISTREAM_DEBUG((cout << m_indentStr << "Break on '" << m_contentStr.substr(m_contentStart, dataStartPos-m_contentStart) << "'" << endl));
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

        string typeStr;
        if (outpObj == NULL)
        {
            MUSHCOREXMLISTREAM_DEBUG((cout << m_indentStr<< "outpObj == NULL" << endl));
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
                outpObj = AllocateVirtual();
            }
        }

        if (outpObj != NULL)
        {
            MUSHCOREXMLISTREAM_DEBUG((cout << m_indentStr << "Threading " << tagStr << endl));
            MUSHCOREXMLISTREAM_DEBUG((m_indentStr += " "));
            
            outpObj->AutoInputPrologue(*this);
            
            if (!outpObj->AutoXMLDataProcess(*this, tagStr))
            {
                Throw("Unrecognised tag '"+tagStr+"'");
            }

            outpObj->AutoInputEpilogue(*this);
            
            MUSHCOREXMLISTREAM_DEBUG((m_indentStr = m_indentStr.substr(0, m_indentStr.size()-1)));
            MUSHCOREXMLISTREAM_DEBUG((cout << m_indentStr << "Unthreading " << tagStr << endl));
        }
        
        string closingTagStr;
        // Consume and check the trailing tag
        while (dataStartPos = TagGet(closingTagStr, m_contentStr, m_contentStart),
               dataStartPos == 0)
        {
            // Can be optimised
            InputFetch();
        }
        MUSHCOREXMLISTREAM_DEBUG((cout<< m_indentStr  << "Consumed end tag '" << m_contentStr.substr(m_contentStart, dataStartPos-m_contentStart) << "'" << endl));
        if (closingTagStr != "/"+tagStr)
        {
            Throw("Unmatched tag: Found '"+closingTagStr+"', expected '/"+tagStr+"'");
        }

        m_contentStart = dataStartPos;
        MUSHCOREXMLISTREAM_DEBUG((cout << m_indentStr << "Checking exit critereon \"" << tagStr << "\" == \"obj\"" << endl));
    } while (tagStr != "obj");
    MUSHCOREXMLISTREAM_DEBUG((cout << m_indentStr << "Exiting" << endl));
    if (m_indentStr == "")
    {
        MUSHCOREXMLISTREAM_DEBUG((MushcoreUtil::BreakpointFunction()));
    }
}

void
MushcoreXMLIStream::ObjectReadVirtual(MushcoreVirtualObject& outObj)
{
    MushcoreVirtualObject *pObj = &outObj;
    ObjectRead(pObj);
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
MushcoreXMLIStream::ObjectRead(tXMLVal& outObj)
{
    string dataStr = DataUntilTake(",)=<");
    istringstream dataStream(dataStr);
    if (!(dataStream >> outObj))
    {
        Throw("Read of XML numerical value failed");
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
    U32 originalSize = m_contentStr.size();
    do
    {
        if (m_inStream.eof())
        {
            Throw("Unexpected end of input");
        }
        
        string newStr;

        std::getline(m_inStream, newStr);
        ++m_contentLineNum;

        if (m_inStream.bad())
        {
            Throw("Read failure");
        }
        
		std::size_t startPos;
        while (startPos = newStr.find("<!--"), startPos != string::npos)
        {
            m_contentStr += newStr.substr(0, startPos);
        
			std::size_t endPos;
            
            while (endPos = newStr.find("-->", startPos), endPos == string::npos)
            {
                startPos = 0;
                
                if (m_inStream.eof())
                {
                    Throw("Unexpected end of input");
                }
                
                std::getline(m_inStream, newStr);
                ++m_contentLineNum;                

                if (m_inStream.bad())
                {
                    Throw("Read failure");
                }
            }
            newStr =  newStr.substr(endPos+3);
        }
        m_contentStr += newStr;
    }
    while (m_contentStr.size() == originalSize);
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
	std::size_t startPos = inStr.find('<', inPos);
    if (startPos == string::npos) return 0;
    std::size_t endPos = inStr.find('>', startPos);
    if (endPos == string::npos)
    {
        Throw("Unclosed tag");
    }
    // change to use substr
    outTag = string(inStr, startPos+1, endPos-startPos-1);
    return endPos + 1;
}

bool
MushcoreXMLIStream::CompositePrologue(void)
{
    bool hasTag = false;
    if (ByteGet() == '<')    
    {
        if (DataUntilTake(">") != "<obj")
        {
            Throw("Bad tag at start of composite.  Expecting <obj>");
        }
        ByteTake(); // Consume >
        hasTag = true;
    }
    U8 byteValue = ByteTake();
    if (byteValue != '(')
    {
        ostringstream message;
        message << "Bad first character in composite.  Should be '(', was '" << byteValue << "'";
        Throw(message.str());
    }
    return hasTag;
}

void
MushcoreXMLIStream::CompositeEpilogue(bool inHasTag)
{
    if (inHasTag)
    {
        if (ByteGet() == '<')    
        {
            if (DataUntilTake(">") != "</obj")
            {
                Throw("Bad tag at end of composite.  Expecting </obj>");
            }
            ByteTake(); // Consume >
        }                
    }
}

void
MushcoreXMLIStream::Throw(const string& inMessage) const
{
    ostringstream message;
    message << "XML parsing failure around '" << m_contentStr.substr(m_contentStart) << "' in element ending at line " << m_contentLineNum << ": " << inMessage;
    throw(MushcoreSyntaxFail(message.str()));
}

MushcoreVirtualObject *
MushcoreXMLIStream::AllocateVirtual(void)
{
    MushcoreVirtualObject *retPtr = NULL;

    string typeStr;
    
    if (!MushcoreUtil::XMLAttributeExtract(typeStr, TagDataGet(), "type"))
    {
        Throw("No type= attribute for polymorphic object '"+TagDataGet()+"'");
//        ObjectReadVirtual(retPtr);
    }
    else
    {
        retPtr = dynamic_cast<MushcoreVirtualObject *>(MushcoreFactory::Sgl().ObjectCreate(typeStr));
        
        if (retPtr == NULL)
        {
            // Dynamic cast failed
            Throw("Object of type "+typeStr+" not castable to MushcoreVirtualObject");
        }
        MUSHCOREXMLISTREAM_DEBUG((cout << m_indentStr << "***** Allocated virtual type '" << typeStr << "'" << endl));
    }
    return retPtr;
}    

