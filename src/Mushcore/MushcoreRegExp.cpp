/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MushcoreRegExp.cpp,v 1.10 2002/12/29 20:59:51 southa Exp $
 * $Log: MushcoreRegExp.cpp,v $
 * Revision 1.10  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.9  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.3  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.1  2002/03/18 22:21:12  southa
 * Initial wrangle command
 *
 */

#include "MushcoreRegExp.h"

using namespace Mushware;
using namespace std;

void MushcoreRegExp::SearchPatternSet(const std::string& inPattern)
{
    if (m_re != NULL) pcre_free(m_re);
    m_re = pcre_compile(
                      inPattern.c_str(),        /* the pattern */
                      0,                        /* default options */
                      &m_error,	    	    	/* for error message */
                      &m_erroffset,     	/* for error offset */
                      NULL);                    /* use default character tables */
    if (m_re == NULL)
    {
        std::ostringstream message;
        message << "Regular expresion '" << inPattern << "' compilation failed at offset " << m_erroffset << ": " << m_error;
        throw MushcoreRegExpFail(message.str());
    }
}

bool MushcoreRegExp::Search(const std::string& inString)
{
    if (m_re == NULL) throw MushcoreRegExpFail("Search with specifying pattern");
    
    int rc;
    rc = pcre_exec(
        m_re,           	/* result of pcre_compile() */
        NULL,           	/* we didn't study the pattern */
        inString.data(), 	/* the subject string */
        inString.size(),    	/* the length of the subject string */
        0,              	/* start at offset 0 in the subject */
        0,              	/* default options */
        NULL,			/* vector for substring information */
        0); 			/* number of elements in the vector */

    return HandleRC(rc);
}

bool MushcoreRegExp::HandleRC(int inRC)
{
    switch (inRC)
    {
        case PCRE_ERROR_NOMATCH:
            return false;

        case PCRE_ERROR_NULL:
            throw MushcoreRegExpFail("Null string");

        case PCRE_ERROR_BADOPTION:
            throw MushcoreRegExpFail("Bad option");

        case PCRE_ERROR_BADMAGIC:
            throw MushcoreRegExpFail("Bad magic number");

        case PCRE_ERROR_UNKNOWN_NODE:
            throw MushcoreRegExpFail("Unknown mode");

        case PCRE_ERROR_NOMEMORY:
            throw MushcoreRegExpFail("Out of memory");

        case PCRE_ERROR_NOSUBSTRING:
            throw MushcoreRegExpFail("No substring");

        default:
            return true;
    }
}

bool MushcoreRegExp::Search(const std::string& inString, std::vector<std::string>& outMatches)
{
    if (m_re == NULL) throw MushcoreRegExpFail("Search with specifying pattern");

    int rc;
    int ovector[768];
    rc = pcre_exec(
        m_re,           	/* result of pcre_compile() */
        NULL,           	/* we didn't study the pattern */
        inString.data(), 	/* the subject string */
        inString.size(),        /* the length of the subject string */
        0,              	/* start at offset 0 in the subject */
        0,              	/* default options */
        ovector,        	/* vector for substring information */
        768); 			/* number of elements in the vector */

    for (int i=1; i<rc; i++)
    {
        outMatches.push_back(std::string(inString.data(), ovector[2*i], ovector[2*i+1] - ovector[2*i]));
    }
    return HandleRC(rc);
}

bool MushcoreRegExp::Search(const std::string& inString, const std::string& inPattern)
{
    SearchPatternSet(inPattern);
    return Search(inString);
}

bool MushcoreRegExp::Search(const std::string& inString, const std::string& inPattern, std::vector<std::string>& outMatches)
{
    SearchPatternSet(inPattern);
    return Search(inString, outMatches);
}
