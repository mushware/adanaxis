/*
 * $Id$
 * $Log$
 */

#include "CoreRegExp.hp"
#include <strstream>

void CoreRegExp::SearchPatternSet(const string& inPattern)
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
        char buf[256];
        buf[sizeof(buf)-1]=0;
        ostrstream message(buf,sizeof(buf)-1);
        message << "Regular expresion '" << inPattern << "' compilation failed at offset " << m_erroffset << ": " << m_error;
        throw CoreRegExpFail(message.str());
    }
}
                               
bool CoreRegExp::Search(const string& inString)
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
                   
bool CoreRegExp::Search(const string& inString, vector<string>& outMatches)
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
        outMatches.push_back(string(inString.data(), ovector[2*i], ovector[2*i+1] - ovector[2*i]));
    }
    return HandleRC(rc);
}

bool CoreRegExp::Search(const string& inString, const string& inPattern)
{
    SearchPatternSet(inPattern);
    return Search(inString);
}

bool CoreRegExp::Search(const string& inString, const string& inPattern, vector<string>& outMatches)
{
    SearchPatternSet(inPattern);
    return Search(inString, outMatches);
}
