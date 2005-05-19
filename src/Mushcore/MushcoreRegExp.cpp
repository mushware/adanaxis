//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreRegExp.cpp
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } NwX2oZoV03fnvBpO2sWLsQ
/*
 * $Id: MushcoreRegExp.cpp,v 1.6 2004/01/02 21:13:13 southa Exp $
 * $Log: MushcoreRegExp.cpp,v $
 * Revision 1.6  2004/01/02 21:13:13  southa
 * Source conditioning
 *
 * Revision 1.5  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:09:15  southa
 * Fixed file headers
 *
 * Revision 1.3  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.2  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
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

#include "MushcoreFail.h"

#include "MushcoreSTL.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_PCRE_PCRE_H
#include <pcre/pcre.h>
#else
#ifdef HAVE_PCRE_H
#include <pcre.h>
#else
#include "pcre.h"
#endif
#endif

using namespace Mushware;
using namespace std;

MushcoreRegExp::~MushcoreRegExp()
{
    if (m_regExp != NULL)
    {
        pcre_free(m_regExp);
    }
}

void MushcoreRegExp::SearchPatternSet(const tPattern& inPattern)
{
    const char *errorMessage;
    int errOffset;
    
    if (m_regExp != NULL) pcre_free(m_regExp);
    m_regExp = pcre_compile(
                      inPattern.c_str(),        /* the pattern */
                      0,                        /* default options */
                      &errorMessage,	    	    	/* for error message */
                      &errOffset,     	    /* for error offset */
                      NULL);                    /* use default character tables */

    if (m_regExp == NULL)
    {
        std::ostringstream message;
        message << "Regular expresion '" << inPattern << "' compilation failed at offset " << errOffset << ": " << errorMessage;
        throw MushcoreSyntaxFail(message.str());
    }
}

bool MushcoreRegExp::Search(const std::string& inString)
{
    if (m_regExp == NULL)
    {
        throw MushcoreLogicFail("Search without specifying pattern");
    }
    
    int returnCode;
    returnCode = pcre_exec(
        reinterpret_cast<const pcre *>(m_regExp), /* result of pcre_compile() */
        NULL,               /* we didn't study the pattern */
        inString.data(),    /* the subject string */
        inString.size(),    /* the length of the subject string */
        0,                  /* start at offset 0 in the subject */
        0,                  /* default options */
        NULL,               /* vector for substring information */
        0);                 /* number of elements in the vector */

    return HandleReturnCode(returnCode);
}

bool MushcoreRegExp::HandleReturnCode(int inReturnCode)
{
    switch (inReturnCode)
    {
        case PCRE_ERROR_NOMATCH:
            return false;

        case PCRE_ERROR_NULL:
            throw MushcoreRequestFail("Null string");

        case PCRE_ERROR_BADOPTION:
            throw MushcoreRequestFail("Bad option");

        case PCRE_ERROR_BADMAGIC:
            throw MushcoreRequestFail("Bad magic number");

        case PCRE_ERROR_UNKNOWN_NODE:
            throw MushcoreRequestFail("Unknown mode");

        case PCRE_ERROR_NOMEMORY:
            throw MushcoreRequestFail("Out of memory");

        case PCRE_ERROR_NOSUBSTRING:
            throw MushcoreRequestFail("No substring");

        default:
            return true;
    }
}

bool MushcoreRegExp::Search(tMatches& outMatches, const tPattern& inString)
{
    if (m_regExp == NULL)
    {
        throw MushcoreLogicFail("Search with specifying pattern");
    }
    
    int returnCode;
    int oVector[3*kMaxMatches];
    returnCode = pcre_exec(
        reinterpret_cast<const pcre *>(m_regExp), /* result of pcre_compile() */
        NULL,               /* we didn't study the pattern */
        inString.data(),    /* the subject string */
        inString.size(),    /* the length of the subject string */
        0,                  /* start at offset 0 in the subject */
        0,                  /* default options */
        oVector,            /* vector for substring information */
        3*kMaxMatches);     /* number of elements in the vector */

    for (int i=1; i<returnCode; i++)
    {
        outMatches.push_back(string(inString.data(), oVector[2*i], oVector[2*i+1] - oVector[2*i]));
    }
    return HandleReturnCode(returnCode);
}


