/*
 * $Id: MustlHTTP.cpp,v 1.4 2002/11/20 22:35:27 southa Exp $
 * $Log: MustlHTTP.cpp,v $
 * Revision 1.4  2002/11/20 22:35:27  southa
 * Multiplayer setup
 *
 * Revision 1.3  2002/11/12 17:05:01  southa
 * Tidied localweb server
 *
 * Revision 1.2  2002/11/08 00:15:30  southa
 * Fixed errors
 *
 * Revision 1.1  2002/11/07 00:53:37  southa
 * localweb work
 *
 */

#include "MustlHTTP.h"

#include "MustlData.h"

const char MustlHTTP::m_endl[3]={0x0d, 0x0a, 0};

MustlHTTP::MustlHTTP() :
    m_refresh(0),
    m_title("mushware"),
    m_allowCaching(false)
{
}

void
MustlHTTP::Reply200(void)
{
    m_content << "HTTP/1.1 200 OK" << m_endl;
}

void
MustlHTTP::ContentTypeHTML(void)
{
    m_content << "Content-Type: text/html; charset=ISO-8859-1" << m_endl;
    m_content << "Connection: close" << m_endl;
    if (!m_allowCaching) m_content << "Expires: 0" << m_endl;
}

void
MustlHTTP::ContentType(const string& inStr)
{
    m_content << "Content-Type: " << inStr << m_endl;
    m_content << "Connection: close" << m_endl;
    if (!m_allowCaching) m_content << "Expires: 0" << m_endl;
}

void
MustlHTTP::Endl(void)
{
    m_content << m_endl;
}

void
MustlHTTP::Header(void)
{
    m_content << "<html>" << m_endl;
    m_content << "<head>" << m_endl;
    m_content << "<link rel=\"StyleSheet\" href=\"/style.css\" type=\"text/css\">" << m_endl;
    m_content << "<title>" << m_title << "</title>" << m_endl;
    if (m_refresh != 0)
    {
        m_content << "<meta http-equiv=Refresh content=\"";
        m_content << m_refresh << "\">" << m_endl;
    }
    m_content << "</head>" << m_endl << "<body>" << m_endl;
}

void
MustlHTTP::Footer(void)
{
    m_content << "</body>" << m_endl << "</html>" << m_endl;
}

void
MustlHTTP::ContentGet(MustlData& outData)
{
    outData.Write(m_content.str());
}
