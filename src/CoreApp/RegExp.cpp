/*
 * $Id$
 * $Log$
 */

#include "RegExp.hp"
#include <strstream>

void RegExp::SearchPatternSet(const string& inPattern)
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
        throw RegExpFail(message.str());
    }
}
                               
bool RegExp::Search(const string& inString)
{
    if (m_re == NULL) throw RegExpFail("Search with specifying pattern");
    
    int rc;
    rc = pcre_exec(m_re,           		/* result of pcre_compile() */
                   NULL,           		/* we didn't study the pattern */
                   inString.data(), 		/* the subject string */
                   inString.size(),          	/* the length of the subject string */
                   0,              		/* start at offset 0 in the subject */
                   0,              		/* default options */
                   NULL,        		/* vector for substring information */
                   0); 				/* number of elements in the vector */

    return HandleRC(rc);
}

bool RegExp::HandleRC(int inRC)
{
    switch (inRC)
    {
        case PCRE_ERROR_NOMATCH:
            return false;

        case PCRE_ERROR_NULL:
            throw RegExpFail("Null string");

        case PCRE_ERROR_BADOPTION:
            throw RegExpFail("Bad option");

        case PCRE_ERROR_BADMAGIC:
            throw RegExpFail("Bad magic number");

        case PCRE_ERROR_UNKNOWN_NODE:
            throw RegExpFail("Unknown mode");

        case PCRE_ERROR_NOMEMORY:
            throw RegExpFail("Out of memory");

        case PCRE_ERROR_NOSUBSTRING:
            throw RegExpFail("No substring");

        default:
            return true;
    }
}
                   
bool RegExp::Search(const string& inString, vector<string>& outMatches)
{
    if (m_re == NULL) throw RegExpFail("Search with specifying pattern");

    int rc;
    int ovector[768];
    rc = pcre_exec(
                   m_re,           		/* result of pcre_compile() */
                   NULL,           		/* we didn't study the pattern */
                   inString.data(), 		/* the subject string */
                   inString.size(),          	/* the length of the subject string */
                   0,              		/* start at offset 0 in the subject */
                   0,              		/* default options */
                   ovector,        		/* vector for substring information */
                   768); 			/* number of elements in the vector */

    for (int i=1; i<rc; i++)
    {
        outMatches.push_back(string(inString.data(), ovector[2*i], ovector[2*i+1] - ovector[2*i]));
    }
    return HandleRC(rc);
}

bool RegExp::Search(const string& inString, const string& inPattern)
{
    SearchPatternSet(inPattern);
    return Search(inString);
}

bool RegExp::Search(const string& inString, const string& inPattern, vector<string>& outMatches)
{
    SearchPatternSet(inPattern);
    return Search(inString, outMatches);
}
