/*
 * $Id: MediaNetHTTP.cpp,v 1.2 2002/11/08 00:15:30 southa Exp $
 * $Log: MediaNetHTTP.cpp,v $
 * Revision 1.2  2002/11/08 00:15:30  southa
 * Fixed errors
 *
 * Revision 1.1  2002/11/07 00:53:37  southa
 * localweb work
 *
 */

#include "MediaNetHTTP.h"

#include "MediaNetData.h"

const char MediaNetHTTP::m_endl[3]={0x0d, 0x0a, 0};

MediaNetHTTP::MediaNetHTTP() :
    m_refresh(0),
    m_title("mushware"),
    m_allowCaching(false)
{
}

void
MediaNetHTTP::Reply200(void)
{
    m_content << "HTTP/1.1 200 OK" << m_endl;
}

void
MediaNetHTTP::ContentTypeHTML(void)
{
    m_content << "Content-Type: text/html" << m_endl;
    m_content << "Connection: close" << m_endl;
    if (!m_allowCaching) m_content << "Expires: 0" << m_endl;
}

void
MediaNetHTTP::ContentType(const string& inStr)
{
    m_content << "Content-Type: " << inStr << m_endl;
    m_content << "Connection: close" << m_endl;
    if (!m_allowCaching) m_content << "Expires: 0" << m_endl;
}

void
MediaNetHTTP::Endl(void)
{
    m_content << m_endl;
}

void
MediaNetHTTP::Header(void)
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
MediaNetHTTP::Footer(void)
{
    m_content << "</body>" << m_endl << "</html>" << m_endl;
}

void
MediaNetHTTP::ContentGet(MediaNetData& outData)
{
    outData.Write(m_content.str());
}
