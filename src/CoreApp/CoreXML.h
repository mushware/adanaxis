/*
 * $Id: CoreXML.h,v 1.1 2002/05/10 16:39:38 southa Exp $
 * $Log: CoreXML.h,v $
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
    void ParseStream(istream& inIn);
    void Stop(void);
private:
    static void startElement(void *userData, const char *name, const char **atts);
    static void endElement(void *userData, const char *name);
    static void characterDataHandler(void *userData, const XML_Char *s, int len);

    bool m_continue;
};
