#ifndef CORESCALAR_HP
#define CORESCALAR_HP
/*
 * $Id: CoreScalar.h,v 1.3 2002/05/09 17:10:38 southa Exp $
 * $Log: CoreScalar.h,v $
 * Revision 1.3  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.2  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 * Revision 1.1  2002/03/04 22:30:49  southa
 * Interpreter work
 *
 */

#include "CoreStandard.h"
using namespace std;

class CoreScalar
{
public:
    CoreScalar(int inInt=0): m_tag(kVal), m_val(inInt) {}
    CoreScalar(Val inVal): m_tag(kVal), m_val(inVal) {}
    CoreScalar(const char *inChar): m_tag(kString), m_string(inChar) {}

    void Get(Val &outVal);
    void Get(string& outStr);
    
    CoreScalar& operator=(const char* inChar)
    {
        m_string=inChar;
        m_tag=kString;
        return *this;
    }
    CoreScalar& operator=(const string &inStr)
    {
        m_string=inStr;
        m_tag=kString;
        return *this;
    }
    CoreScalar& operator=(Val inVal)
    {
        m_val=inVal;
        m_tag=kVal;
        return *this;
    }
    
    void ostreamPrint(ostream &inOut) const;

private:
    enum Tag
    {
        kVal,
        kString
    };
    Tag m_tag;
    Val m_val;
    string m_string;
};

inline ostream& operator<<(ostream& inOut, const CoreScalar& inScalar)
{
    inScalar.ostreamPrint(inOut);
    return inOut;
}
#endif
