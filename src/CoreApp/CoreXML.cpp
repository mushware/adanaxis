/*
 * $Id$
 * $Log$
 */

#include "CoreXML.h"
#include "CoreException.h"

void
CoreXML::startElement(void *userData, const char *name, const char **atts)
{
    CoreXML *newThis=static_cast<CoreXML *>(userData);
    cout << "Start of element " << name << endl;
    cout << "Attributes: " << endl;
    const char **ppCh=atts;
    while (*ppCh != NULL)
    {
        cout << *ppCh << endl;
        ppCh++;
    }
}

void
CoreXML::endElement(void *userData, const char *name)
{
    CoreXML *newThis=static_cast<CoreXML *>(userData);
    cout << "End of element " << name << endl;
}

void
CoreXML::characterDataHandler(void *userData, const XML_Char *s, int len)
{
    CoreXML *newThis=static_cast<CoreXML *>(userData);
    string str(s, len);
    cout << "Data: '" << str << "'" << endl;
}

void
CoreXML::ParseStream(istream& inIn)
{
    string str;

    XML_Parser parser = XML_ParserCreate(NULL);
    if (parser == NULL) throw(XMLFail("Couldn't create parser"));
                              
    XML_SetUserData(parser, this);
    XML_SetElementHandler(parser, startElement, endElement);
    XML_SetCharacterDataHandler(parser, characterDataHandler);

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

void CoreXML::Stop(void)
{
    m_continue=false;
}
