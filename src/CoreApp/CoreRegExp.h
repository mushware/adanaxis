/*
 * $Id: CoreRegExp.h,v 1.2 2002/05/09 17:10:38 southa Exp $
 * $Log: CoreRegExp.h,v $
 * Revision 1.2  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.1  2002/03/18 22:21:12  southa
 * Initial wrangle command
 *
 */

#ifndef COREREGEXP_HP
#define COREREGEXP_HP

#include "pcre.h"
#include "CoreStandard.h"

class CoreRegExp
{
public:
    CoreRegExp() {m_re = NULL;}
    CoreRegExp(const std::string& inPattern) {m_re = NULL;SearchPatternSet(inPattern);}
    ~CoreRegExp() {if (m_re != NULL) pcre_free(m_re);}
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

class CoreRegExpFail: public std::exception
{
public:
    CoreRegExpFail(const std::string &inMessage) {m_message=inMessage;}
    ~CoreRegExpFail() throw() {}
    const std::string& SPrint(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}
private:
std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, CoreRegExpFail f)
{
    return s<<f.SPrint();
}

#endif
