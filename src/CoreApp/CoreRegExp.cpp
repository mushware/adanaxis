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
 * $Id: CoreRegExp.cpp,v 1.4 2002/06/27 12:36:04 southa Exp $
 * $Log: CoreRegExp.cpp,v $
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

#include "CoreRegExp.h"

void CoreRegExp::SearchPatternSet(const std::string& inPattern)
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
        throw CoreRegExpFail(message.str());
    }
}

bool CoreRegExp::Search(const std::string& inString)
{
    if (m_re == NULL) throw CoreRegExpFail("Search with specifying pattern");
    
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

bool CoreRegExp::HandleRC(int inRC)
{
    switch (inRC)
    {
        case PCRE_ERROR_NOMATCH:
            return false;

        case PCRE_ERROR_NULL:
            throw CoreRegExpFail("Null string");

        case PCRE_ERROR_BADOPTION:
            throw CoreRegExpFail("Bad option");

        case PCRE_ERROR_BADMAGIC:
            throw CoreRegExpFail("Bad magic number");

        case PCRE_ERROR_UNKNOWN_NODE:
            throw CoreRegExpFail("Unknown mode");

        case PCRE_ERROR_NOMEMORY:
            throw CoreRegExpFail("Out of memory");

        case PCRE_ERROR_NOSUBSTRING:
            throw CoreRegExpFail("No substring");

        default:
            return true;
    }
}

bool CoreRegExp::Search(const std::string& inString, std::vector<std::string>& outMatches)
{
    if (m_re == NULL) throw CoreRegExpFail("Search with specifying pattern");

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

bool CoreRegExp::Search(const std::string& inString, const std::string& inPattern)
{
    SearchPatternSet(inPattern);
    return Search(inString);
}

bool CoreRegExp::Search(const std::string& inString, const std::string& inPattern, std::vector<std::string>& outMatches)
{
    SearchPatternSet(inPattern);
    return Search(inString, outMatches);
}
