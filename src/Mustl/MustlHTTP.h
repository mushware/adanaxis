/*
 * $Id: MustlHTTP.h,v 1.2 2002/11/12 17:05:01 southa Exp $
 * $Log: MustlHTTP.h,v $
 * Revision 1.2  2002/11/12 17:05:01  southa
 * Tidied localweb server
 *
 * Revision 1.1  2002/11/07 00:53:37  southa
 * localweb work
 *
 */

#include "mushCore.h"

class MustlData;

class MustlHTTP
{
public:
    MustlHTTP();
    void Reply200(void);
    void ContentTypeHTML(void);
    void ContentType(const string& inStr);
    void Endl(void);
    void Header(void);
    void Footer(void);
    void AllowCachingSet(void) { m_allowCaching=true; }
    ostringstream& Out(void) { return m_content; }
    void ContentGet(MustlData& outData);
    
private:
    ostringstream m_content;
    U32 m_refresh;    
    string m_title;
    bool m_allowCaching;
    static const char m_endl[3];
};
