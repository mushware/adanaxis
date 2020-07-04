//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXML.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } KwsXmmrwBNAbfI0IZInykA
/*
 * $Id: MushcoreXML.cpp,v 1.12 2006/06/01 15:39:48 southa Exp $
 * $Log: MushcoreXML.cpp,v $
 * Revision 1.12  2006/06/01 15:39:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.10  2005/04/20 22:18:25  southa
 * Mac OS X build fixes
 *
 * Revision 1.9  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:19  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/02/05 17:06:38  southa
 * Build fixes
 *
 * Revision 1.5  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.4  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.3  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 * Revision 1.2  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:08  southa
 * Created Mushcore
 *
 * Revision 1.15  2003/01/07 17:13:40  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.14  2002/12/29 20:59:52  southa
 * More build fixes
 *
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
 * MushcoreXML loader
 *
 * Revision 1.2  2002/05/25 17:17:18  southa
 * MushcoreXML implementation
 *
 * Revision 1.1  2002/05/24 18:08:35  southa
 * MushcoreXML and game map
 *
 */

#include "MushcoreXML.h"
#include "MushcoreFail.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

void
MushcoreXMLHandler::XMLDataHandler(MushcoreXML& inXML)
{
    // Key function
}

MushcoreXML::MushcoreXML(istream& inStream, const string& inName, U32 inLine):
    m_currentHandler(NULL),
    m_inStream(&inStream),
    m_name(inName),
    m_threaded(false),
    m_line(inLine)
{
#ifdef MUSHCORE_USE_EXPAT        
    m_parser = XML_ParserCreate(NULL);
    if (m_parser == NULL) throw(MushcoreSyntaxFail("Couldn't create parser"));
    XML_SetUserData(m_parser, this);
    XML_SetElementHandler(m_parser, StartElementHandler, EndElementHandler);
    XML_SetCharacterDataHandler(m_parser, CharacterDataHandler);
#else    
    throw MushcoreLogicFail("Couldn't create parser - expat not compiled in");
#endif
}

MushcoreXML::~MushcoreXML()
{
#ifdef MUSHCORE_USE_EXPAT        
    XML_ParserFree(m_parser);
#endif
}

void
MushcoreXML::ProcessStartElement(const char *inName, const char **inAttribs)
{
    m_tagStack.push(inName);
    m_dataStack.push(string());
    m_attribStack.push(map<std::string, string>());
    while (*inAttribs != NULL)
    {
        m_attribStack.top()[inAttribs[0]]=inAttribs[1];
        inAttribs+=2;
    }
    MUSHCOREASSERT(m_currentHandler != NULL);
    m_currentHandler->XMLStartHandler(*this);
}

void
MushcoreXML::ProcessEndElement(const char *inName)
{
    if (TopTag() != inName)
    {
        ostringstream message;
        message << "Tag mismatch <" << TopTag() << "> != </" << inName << ">";
        throw (MushcoreSyntaxFail(message.str()));
    }
    MUSHCOREASSERT(m_currentHandler != NULL);
    m_currentHandler->XMLEndHandler(*this);
    m_attribStack.pop();
    m_dataStack.pop();
    m_tagStack.pop();
}

void
MushcoreXML::ProcessCharacterData(const char *inData, U32 inLen)
{
    m_dataStack.top().append(inData, inLen);
    MUSHCOREASSERT(m_currentHandler != NULL);
    m_currentHandler->XMLDataHandler(*this);
}

void
MushcoreXML::StartElementHandler(void *inUserData, const char *inName, const char **inAttribs)
{
    MushcoreXML *newThis=static_cast<MushcoreXML *>(inUserData);
    newThis->ProcessStartElement(inName, inAttribs);
}

void
MushcoreXML::EndElementHandler(void *inUserData, const char *inName)
{
    MushcoreXML *newThis=static_cast<MushcoreXML *>(inUserData);
    newThis->ProcessEndElement(inName);
}

void
#ifdef MUSHCORE_USE_EXPAT        
MushcoreXML::CharacterDataHandler(void *inUserData, const XML_Char *inData, int inLen)
#else
MushcoreXML::CharacterDataHandler(void *inUserData, const char *inData, int inLen)
#endif
{
    MushcoreXML *newThis=static_cast<MushcoreXML *>(inUserData);
    newThis->ProcessCharacterData(inData, inLen);
}

MushcoreScalar
MushcoreXML::GetAttrib(const string& inName)
{
    map<std::string, string>::const_iterator p = TopAttrib().find(inName);
    if (p != TopAttrib().end())
    {
        return MushcoreScalar(p->second);
    }
    else
    {
        return MushcoreScalar("");
    }
}

void
MushcoreXML::GetAttrib(MushcoreScalar& outScalar, const string& inName)
{
    map<std::string, string>::const_iterator p = TopAttrib().find(inName);
    if (p != TopAttrib().end())
    {
        outScalar=p->second;
    }
}

MushcoreScalar
MushcoreXML::GetAttribOrThrow(const string& inName)
{

    map<std::string, string>::const_iterator p = TopAttrib().find(inName);
    if (p == TopAttrib().end())
    {
        ostringstream message;
        message << "Missing essential attribute '" << inName << "'";
        Throw(message.str());
    }
    return MushcoreScalar(p->second);
}

void
MushcoreXML::Throw(const string& inMessage)
{
    ostringstream message;
    message << "XML parsing failure in " << m_name << " at line " << m_line << ": " << inMessage << endl;
    DumpTops(message);
    throw(MushcoreSyntaxFail(message.str()));
}

void
MushcoreXML::DumpTops(ostream& inOut)
{
    if (!m_tagStack.empty())
    {
        inOut << "Current tag <" << TopTag() << ">:" << endl;
    }
    if (!m_attribStack.empty())
    {
        inOut << "Attribs: " << endl;
        for (map<std::string, string>::const_iterator p = TopAttrib().begin();
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
MushcoreXML::NewHandler(MushcoreXMLHandler& inHandler)
{
    m_handlers.push(&inHandler);
    m_currentHandler=&inHandler;
}

void
MushcoreXML::ParseStream(MushcoreXMLHandler& inHandler)
{
#ifdef MUSHCORE_USE_EXPAT
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
                throw (MushcoreSyntaxFail(message.str()));
            }
            m_line++;
        } while (m_continue && !m_inStream->eof());
        m_threaded=false;
    }
#endif
}

void MushcoreXML::StopHandler(void)
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
