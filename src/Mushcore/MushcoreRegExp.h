#ifndef MUSHCOREREGEXP_H
#define MUSHCOREREGEXP_H
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
 * $Id: MushcoreRegExp.h,v 1.8 2002/12/20 13:17:33 southa Exp $
 * $Log: MushcoreRegExp.h,v $
 * Revision 1.8  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.6  2002/09/01 16:29:18  southa
 * Support Redhat paths for include files
 *
 * Revision 1.5  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.1  2002/03/18 22:21:12  southa
 * Initial wrangle command
 *
 */

#ifndef COREREGEXP_H
#define COREREGEXP_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_PCRE_H
#include <pcre.h>
#else
#ifdef HAVE_PCRE_PCRE_H
#include <pcre/pcre.h>
#else
#include "pcre.h"
#endif
#endif

#include "MushcoreStandard.h"

class MushcoreRegExp
{
public:
    MushcoreRegExp() {m_re = NULL;}
    MushcoreRegExp(const std::string& inPattern) {m_re = NULL;SearchPatternSet(inPattern);}
    ~MushcoreRegExp() {if (m_re != NULL) pcre_free(m_re);}
    void SearchPatternSet(const std::string& inPattern);
    bool Search(const std::string& inString);
    bool Search(const std::string& inString, std::vector<std::string>& outMatches);
    bool Search(const std::string& inString, const std::string& inPattern);
    bool Search(const std::string& inString, const std::string& inPattern, std::vector<std::string>& outMatches);

private:
    bool HandleRC(int inRC);
        
    pcre *m_re;
    const char *m_error;
    int m_erroffset;
};

class MushcoreRegExpFail: public std::exception
{
public:
    MushcoreRegExpFail(const std::string &inMessage) {m_message=inMessage;}
    ~MushcoreRegExpFail() throw() {}
    const std::string& SPrint(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}
private:
std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, MushcoreRegExpFail f)
{
    return s<<f.SPrint();
}

#endif
#endif
