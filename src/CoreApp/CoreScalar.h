#ifndef CORESCALAR_HP
#define CORESCALAR_HP
/*
 * $Id: CoreScalar.h,v 1.6 2002/05/28 22:36:44 southa Exp $
 * $Log: CoreScalar.h,v $
 * Revision 1.6  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.5  2002/05/28 13:05:56  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.4  2002/05/27 12:58:43  southa
 * GameContract and global configs added
 *
 * Revision 1.3  2002/05/26 16:35:07  southa
 * CoreXML work
 *
 * Revision 1.2  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
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
    CoreScalar(): m_tag(kNone) {}
    // CoreScalar(int inInt=0): m_tag(kVal), m_val(inInt) {}
    CoreScalar(tVal inVal): m_tag(kVal), m_val(inVal) {}
    // CoreScalar(const char *inChar): m_tag(kString), m_string(inChar) {}
    CoreScalar(const string& inStr): m_tag(kString), m_string(inStr) {}

    void Get(tVal &outVal) const;
    void Get(string& outStr) const;

    string StringGet(void) const {string outStr; Get(outStr); return outStr;}
    tVal ValGet(void) const {tVal outVal; Get(outVal); return outVal;}
    U32 U32Get(void) const {tVal outVal; Get(outVal); return static_cast<U32>(outVal);}

    inline bool Equals(const CoreScalar& inScalar) const
    {
        if (m_tag == kVal && inScalar.m_tag ==  kVal)
        {
            return m_val == inScalar.m_val;
        }
        return SlowEquals(inScalar);        
    }

    bool SlowEquals(const CoreScalar& inScalar) const;

    CoreScalar& operator=(const string &inStr)
    {
        m_string=inStr;
        m_tag=kString;
        return *this;
    }
    CoreScalar& operator=(tVal inVal)
    {
        m_val=inVal;
        m_tag=kVal;
        return *this;
    }

    // Conversion operators
    // operator tVal() const { return Val(); }
    // operator string() const { return String(); }
    
    void ostreamPrint(ostream &inOut) const;

private:
    enum Tag
    {
        kNone,
        kVal,
        kString
    };
    Tag m_tag;
    tVal m_val;
    string m_string;
};

inline bool operator==(const CoreScalar& a, const CoreScalar& b)
{
    return a.Equals(b);
}

inline bool operator!=(const CoreScalar& a, const CoreScalar& b)
{
    return !a.Equals(b);
}

inline ostream& operator<<(ostream& inOut, const CoreScalar& inScalar)
{
    inScalar.ostreamPrint(inOut);
    return inOut;
}
#endif
