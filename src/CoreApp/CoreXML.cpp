/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: CoreXML.cpp,v 1.13 2002/12/20 13:17:34 southa Exp $
 * $Log: CoreXML.cpp,v $
 * Revision 1.13  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.12  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.11  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.10  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.9  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.8  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.7  2002/06/04 17:01:20  southa
 * More work
 *
 * Revision 1.6  2002/06/04 14:11:21  southa
 * Traits loader first stage
 *
 * Revision 1.5  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.4  2002/05/28 13:05:56  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.3  2002/05/26 16:08:48  southa
 * CoreXML loader
 *
 * Revision 1.2  2002/05/25 17:17:18  southa
 * CoreXML implementation
 *
 * Revision 1.1  2002/05/24 18:08:35  southa
 * CoreXML and game map
 *
 */

#include "CoreXML.h"
#include "CoreException.h"

using namespace Mushware;
using namespace std;


CoreXML::CoreXML(istream& inStream, const string& inName = "<unknown stream>", U32 inLine=1):
    m_currentHandler(NULL), m_inStream(&inStream), m_name(inName), m_threaded(false), m_line(inLine)
{
    m_parser = XML_ParserCreate(NULL);
    if (m_parser == NULL) throw(XMLFail("Couldn't create parser"));
    XML_SetUserData(m_parser, this);
    XML_SetElementHandler(m_parser, StartElementHandler, EndElementHandler);
    XML_SetCharacterDataHandler(m_parser, CharacterDataHandler);
}

CoreXML::~CoreXML()
{
    XML_ParserFree(m_parser);
}

void
CoreXML::ProcessStartElement(const char *inName, const char **inAttribs)
{
    m_tagStack.push(inName);
    m_dataStack.push(string());
    m_attribStack.push(map<string, string>());
    while (*inAttribs != NULL)
    {
        m_attribStack.top()[inAttribs[0]]=inAttribs[1];
        inAttribs+=2;
    }
    COREASSERT(m_currentHandler != NULL);
    m_currentHandler->XMLStartHandler(*this);
}

void
CoreXML::ProcessEndElement(const char *inName)
{
    if (TopTag() != inName)
    {
        ostringstream message;
        message << "Tag mismatch <" << TopTag() << "> != </" << inName << ">";
        throw (XMLFail(message.str()));
    }
    COREASSERT(m_currentHandler != NULL);
    m_currentHandler->XMLEndHandler(*this);
    m_attribStack.pop();
    m_dataStack.pop();
    m_tagStack.pop();
}

void
CoreXML::ProcessCharacterData(const char *inData, tSize inLen)
{
    m_dataStack.top().append(inData, inLen);
    COREASSERT(m_currentHandler != NULL);
    m_currentHandler->XMLDataHandler(*this);
}

void
CoreXML::StartElementHandler(void *inUserData, const char *inName, const char **inAttribs)
{
    CoreXML *newThis=static_cast<CoreXML *>(inUserData);
    newThis->ProcessStartElement(inName, inAttribs);
}

void
CoreXML::EndElementHandler(void *inUserData, const char *inName)
{
    CoreXML *newThis=static_cast<CoreXML *>(inUserData);
    newThis->ProcessEndElement(inName);
}

void
CoreXML::CharacterDataHandler(void *inUserData, const XML_Char *inData, int inLen)
{
    CoreXML *newThis=static_cast<CoreXML *>(inUserData);
    newThis->ProcessCharacterData(inData, inLen);
}

CoreScalar
CoreXML::GetAttrib(const string& inName)
{
    map<string, string>::const_iterator p = TopAttrib().find(inName);
    if (p != TopAttrib().end())
    {
        return p->second;
    }
    else
    {
        return string("");
    }
}

void
CoreXML::GetAttrib(CoreScalar& outScalar, const string& inName)
{
    map<string, string>::const_iterator p = TopAttrib().find(inName);
    if (p != TopAttrib().end())
    {
        outScalar=p->second;
    }
}

CoreScalar
CoreXML::GetAttribOrThrow(const string& inName)
{

    map<string, string>::const_iterator p = TopAttrib().find(inName);
    if (p == TopAttrib().end())
    {
        ostringstream message;
        message << "Missing essential attribute '" << inName << "'";
        Throw(message.str());
    }
    return p->second;
}

void
CoreXML::Throw(const string& inMessage)
{
    ostringstream message;
    message << "XML parsing failure in " << m_name << " at line " << m_line << ": " << inMessage << endl;
    DumpTops(message);
    throw(XMLFail(message.str()));
}

void
CoreXML::DumpTops(ostream& inOut)
{
    if (!m_tagStack.empty())
    {
        inOut << "Current tag <" << TopTag() << ">:" << endl;
    }
    if (!m_attribStack.empty())
    {
        inOut << "Attribs: " << endl;
        for (map<string, string>::const_iterator p = TopAttrib().begin();
             p != TopAttrib().end(); p++)
        {
            inOut << p->first << " = " << p->second << endl;
        }
    }
    if (!m_dataStack.empty())
    {
        inOut << "Data: '" << TopData() << "'" << endl;
    }
}

void
CoreXML::NewHandler(CoreXMLHandler& inHandler)
{
    m_handlers.push(&inHandler);
    m_currentHandler=&inHandler;
}

void
CoreXML::ParseStream(CoreXMLHandler& inHandler)
{
    NewHandler(inHandler);
    if (!m_threaded)
    {
        string str;
        m_threaded=true;
        m_continue=true;

        do
        {
            getline(*m_inStream, str);
            if (!m_inStream->eof()) str.append("\n");
            if (!XML_Parse(m_parser, str.data(), str.length(), m_inStream->eof()))
            {
                ostringstream message;
                message << XML_ErrorString(XML_GetErrorCode(m_parser)) << " at line " <<
                    XML_GetCurrentLineNumber(m_parser);
                throw (XMLFail(message.str()));
            }
            m_line++;
        } while (m_continue && !m_inStream->eof());
        m_threaded=false;
    }
}

void CoreXML::StopHandler(void)
{
    if (!m_handlers.empty()) m_handlers.pop();
    if (m_handlers.empty())
    {
        // Should set a null handler really
        m_continue=false;
    }
    else
    {
        m_currentHandler=m_handlers.top();
    }
}
