//%includeGuardStart {
#ifndef MUSHCOREXML_H
#define MUSHCOREXML_H
//%includeGuardStart } FG9UxxwHIoPuD15z+L32yA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXML.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } vVslL/TgxkMLTD73bl9ejA
/*
 * $Id: MushcoreXML.h,v 1.7 2004/01/02 21:13:14 southa Exp $
 * $Log: MushcoreXML.h,v $
 * Revision 1.7  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:19  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/20 12:23:24  southa
 * Code and interface tidying
 *
 * Revision 1.3  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.2  2003/01/11 13:03:18  southa
 * Use Mushcore header
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
 * Revision 1.13  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.12  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.10  2002/09/01 16:29:18  southa
 * Support Redhat paths for include files
 *
 * Revision 1.9  2002/08/27 08:56:18  southa
 * Source conditioning
 *
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
 * MushcoreXML loader
 *
 * Revision 1.3  2002/05/25 17:17:18  southa
 * MushcoreXML implementation
 *
 * Revision 1.2  2002/05/24 18:08:35  southa
 * MushcoreXML and game map
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

#include "MushcoreStandard.h"

#ifdef MUSHCORE_USE_EXPAT

// Interface to XML parser 
extern "C"
{
#ifdef HAVE_EXPAT_H
#include <expat.h>
#else
#ifdef HAVE_EXPAT_EXPAT_H
#include <expat/expat.h>
#else
#include "expat.h"
#endif
#endif
}

#endif

#include "MushcoreScalar.h"

class MushcoreXML;

// Clients should privately inherit this
class MushcoreXMLHandler
{
public:
    virtual void XMLStartHandler(MushcoreXML& inXML) {}
    virtual void XMLEndHandler(MushcoreXML& inXML) = 0;
    virtual void XMLDataHandler(MushcoreXML& inXML);
};

class MushcoreXML
{
public:
    MushcoreXML(std::istream& inStream, const std::string& inName = "<unknown stream>", Mushware::U32 inLine=1);
    ~MushcoreXML();
    
    const std::string& TopTag(void) {MUSHCOREASSERT(!m_tagStack.empty());return m_tagStack.top();}
    const std::string& TopData(void) {MUSHCOREASSERT(!m_dataStack.empty());return m_dataStack.top();}
    std::map<std::string, std::string>& TopAttrib(void) {MUSHCOREASSERT(!m_attribStack.empty());return m_attribStack.top();}
    void DumpTops(std::ostream& inOut);
    void StopHandler(void);
    MushcoreScalar GetAttrib(const std::string& inName);
    void GetAttrib(MushcoreScalar& outScalar, const std::string& inName);
    MushcoreScalar GetAttribOrThrow(const std::string& inName);
    void Throw(const std::string& inMessage);
    void ParseStream(MushcoreXMLHandler& inHandler);

private:
    void ProcessStartElement(const char *inName, const char **inAttribs);
    void ProcessEndElement(const char *inName);
    void ProcessCharacterData(const char *inData, Mushware::U32 inLen);
    void NewHandler(MushcoreXMLHandler& inHandler);
    static void StartElementHandler(void *inUserData, const char *inName, const char **inAttribs);
    static void EndElementHandler(void *inUserData, const char *inName);
#ifdef MUSHCORE_USE_EXPAT
    static void CharacterDataHandler(void *inUserData, const XML_Char *inData, int inLen);
#else
    static void CharacterDataHandler(void *inUserData, const char *inData, int inLen);
#endif    

    MushcoreXMLHandler *m_currentHandler;
    std::stack<MushcoreXMLHandler *> m_handlers;
#ifdef MUSHCORE_USE_EXPAT
    XML_Parser m_parser;
#endif
    std::stack< std::map<std::string, std::string> > m_attribStack;
    std::stack<std::string> m_dataStack;
    std::stack<std::string> m_tagStack;
    std::istream *m_inStream;
    std::string m_name;
    bool m_continue;
    bool m_threaded;
    Mushware::U32 m_line;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
