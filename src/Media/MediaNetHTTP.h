/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

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
    
    ostringstream& Out(void) { return m_content; }
    const ostringstream& ContentGet(void) { return m_content; }
    
private:
    ostringstream m_content;
    U32 m_refresh;    
    string m_title;
    static const char m_endl[3];
};


