/*
 * $Id: CoreXML.cpp,v 1.1 2002/05/24 18:08:35 southa Exp $
 * $Log: CoreXML.cpp,v $
 * Revision 1.1  2002/05/24 18:08:35  southa
 * CoreXML and game map
 *
 */

#include "CoreXML.h"
#include "CoreException.h"

void
CoreXML::XMLStartElement(void)
{
}

void
CoreXML::XMLEndElement(void)
{
}

void
CoreXML::XMLCharacterData(void)
{
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
    XMLStartElement();
}

void
CoreXML::ProcessEndElement(const char *inName)
{
    if (XMLTopTag() != inName)
    {
        ostringstream message;
        message << "Tag mismatch <" << XMLTopTag() << "> != </" << inName << ">";
        throw (XMLFail(message.str()));
    }
    XMLEndElement();
    m_attribStack.pop();
    m_dataStack.pop();
    m_tagStack.pop();
}

void
CoreXML::ProcessCharacterData(const char *inData, tSize inLen)
{
    m_dataStack.top().append(inData, inLen);
    XMLCharacterData();
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

void
CoreXML::XMLDumpTops(ostream& inOut)
{
    inOut << "Data for tag <" << XMLTopTag() << ">:" << endl;
    inOut << "Attribs were: " << endl;
    for (map<string, string>::const_iterator p = XMLTopAttrib().begin();
         p != XMLTopAttrib().end(); p++)
    {
        inOut << p->first << " = " << p->second << endl;
    }

    inOut << "Data: '" << XMLTopData() << "'" << endl;
}

void
CoreXML::XMLParseStream(istream& inIn)
{
    string str;

    XML_Parser parser = XML_ParserCreate(NULL);
    if (parser == NULL) throw(XMLFail("Couldn't create parser"));
                              
    XML_SetUserData(parser, this);
    XML_SetElementHandler(parser, StartElementHandler, EndElementHandler);
    XML_SetCharacterDataHandler(parser, CharacterDataHandler);

    m_continue=true;
    
    do
    {
        getline(inIn, str);
        if (!XML_Parse(parser, str.data(), str.length(), inIn.eof()))
        {
            ostringstream message;
            message << XML_ErrorString(XML_GetErrorCode(parser)) << " at line " <<
                XML_GetCurrentLineNumber(parser);
            XML_ParserFree(parser);
            throw (XMLFail(message.str()));
        }
    } while (m_continue && !inIn.eof());

    XML_ParserFree(parser);
}

void CoreXML::XMLStop(void)
{
    m_continue=false;
}
