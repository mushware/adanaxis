#ifndef COREXML_H
#define COREXML_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/




/*
 * $Id: CoreXML.h,v 1.8 2002/08/07 13:36:46 southa Exp $
 * $Log: CoreXML.h,v $
 * Revision 1.8  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.7  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.6  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.5  2002/06/04 14:11:21  southa
 * Traits loader first stage
 *
 * Revision 1.4  2002/05/26 16:08:49  southa
 * CoreXML loader
 *
 * Revision 1.3  2002/05/25 17:17:18  southa
 * CoreXML implementation
 *
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
#include "CoreScalar.h"

class CoreXML;

// Clients should privately inherit this
class CoreXMLHandler
{
public:
    virtual void XMLStartHandler(CoreXML& inXML) {}
    virtual void XMLEndHandler(CoreXML& inXML) = 0;
    virtual void XMLDataHandler(CoreXML& inXML) {}
};

class CoreXML
{
public:
    CoreXML(istream& inStream, const string& inName = "<unknown stream>", U32 inLine=1);
    ~CoreXML();
    
    const string& TopTag(void) {COREASSERT(!m_tagStack.empty());return m_tagStack.top();}
    const string& TopData(void) {COREASSERT(!m_dataStack.empty());return m_dataStack.top();}
    map<string, string>& TopAttrib(void) {COREASSERT(!m_attribStack.empty());return m_attribStack.top();}
    void DumpTops(ostream& inOut);
    void StopHandler(void);
    CoreScalar GetAttrib(const string& inName);
    void GetAttrib(CoreScalar& outScalar, const string& inName);
    CoreScalar GetAttribOrThrow(const string& inName);
    void Throw(const string& inMessage);
    void ParseStream(CoreXMLHandler& inHandler);

private:
    void ProcessStartElement(const char *inName, const char **inAttribs);
    void ProcessEndElement(const char *inName);
    void ProcessCharacterData(const char *inData, tSize inLen);
    void NewHandler(CoreXMLHandler& inHandler);
    static void StartElementHandler(void *inUserData, const char *inName, const char **inAttribs);
    static void EndElementHandler(void *inUserData, const char *inName);
    static void CharacterDataHandler(void *inUserData, const XML_Char *inData, int inLen);

    CoreXMLHandler *m_currentHandler;
    stack<CoreXMLHandler *> m_handlers;
    XML_Parser m_parser;
    stack< map<string, string> > m_attribStack;
    stack<string> m_dataStack;
    stack<string> m_tagStack;
    istream *m_inStream;
    string m_name;
    bool m_continue;
    bool m_threaded;
    U32 m_line;
};
#endif
