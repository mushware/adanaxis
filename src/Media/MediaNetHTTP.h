/*
 * $Id: MediaNetHTTP.h,v 1.1 2002/11/07 00:53:37 southa Exp $
 * $Log: MediaNetHTTP.h,v $
 * Revision 1.1  2002/11/07 00:53:37  southa
 * localweb work
 *
 */

#include "mushCore.h"

class MediaNetData;

class MediaNetHTTP
{
public:
    MediaNetHTTP();
    void Reply200(void);
    void ContentTypeHTML(void);
    void ContentType(const string& inStr);
    void Endl(void);
    void Header(void);
    void Footer(void);
    void AllowCachingSet(void) { m_allowCaching=true; }
    ostringstream& Out(void) { return m_content; }
    void ContentGet(MediaNetData& outData);
    
private:
    ostringstream m_content;
    U32 m_refresh;    
    string m_title;
    bool m_allowCaching;
    static const char m_endl[3];
};
