/*
 * $Id: CoreXML.h,v 1.2 2002/05/24 18:08:35 southa Exp $
 * $Log: CoreXML.h,v $
 * Revision 1.2  2002/05/24 18:08:35  southa
 * CoreXML and game map
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/02/23 23:58:45  southa
 * Made buildable for cygwin
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

// Interface to XML parser 
extern "C"
{
#include "expat.h"
}

#include "CoreStandard.h"

class CoreXML
{
public:
    virtual ~CoreXML() {}

protected:
    virtual void XMLStartElement(void);
    virtual void XMLEndElement(void);
    virtual void XMLCharacterData(void);

    void XMLParseStream(istream& inIn);
    void XMLStop(void);
    const string& XMLTopTag(void) {return m_tagStack.top();}
    const string& XMLTopData(void) {return m_dataStack.top();}
    const map<string, string>& XMLTopAttrib(void) {return m_attribStack.top();}
    void XMLDumpTops(ostream& inOut);
    
private:
    void ProcessStartElement(const char *inName, const char **inAttribs);
    void ProcessEndElement(const char *inName);
    void ProcessCharacterData(const char *inData, tSize inLen);
    static void StartElementHandler(void *inUserData, const char *inName, const char **inAttribs);
    static void EndElementHandler(void *inUserData, const char *inName);
    static void CharacterDataHandler(void *inUserData, const XML_Char *inData, int inLen);
        
    bool m_continue;
    stack< map<string, string> > m_attribStack;
    stack<string> m_dataStack;
    stack<string> m_tagStack;
};
