#ifndef MUSHCORESCALAR_H
#define MUSHCORESCALAR_H
#ifndef CORESCALAR_H
#define CORESCALAR_H
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
 * $Id: MushcoreScalar.h,v 1.16 2002/12/29 20:30:51 southa Exp $
 * $Log: MushcoreScalar.h,v $
 * Revision 1.16  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.15  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.14  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.13  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.12  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.11  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.10  2002/07/31 16:27:15  southa
 * Collision checking work
 *
 * Revision 1.9  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.8  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.7  2002/06/04 20:27:35  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
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
 * MushcoreXML work
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

#include "MushcoreStandard.h"

class MushcoreScalar
{
public:
    MushcoreScalar(): m_tag(kNone) {}
    // MushcoreScalar(int inInt=0): m_tag(kVal), m_val(inInt) {}
    MushcoreScalar(Mushware::tVal inVal): m_tag(kVal), m_val(inVal) {}
    // MushcoreScalar(const char *inChar): m_tag(kString), m_string(inChar) {}
    MushcoreScalar(const std::string& inStr): m_tag(kString), m_string(inStr) {}

    void Get(Mushware::tVal &outVal) const;
    void Get(std::string& outStr) const;
    void Get(bool& outBool) const;

    std::string StringGet(void) const {std::string outStr; Get(outStr); return outStr;}
    Mushware::tVal ValGet(void) const {Mushware::tVal outVal; Get(outVal); return outVal;}
    Mushware::U32 U32Get(void) const {Mushware::tVal outVal; Get(outVal); return static_cast<Mushware::U32>(outVal);}
    bool BoolGet(void) const {bool outVal; Get(outVal); return outVal;}

    inline bool Equals(const MushcoreScalar& inScalar) const
    {
        if (m_tag == kVal && inScalar.m_tag ==  kVal)
        {
            return m_val == inScalar.m_val;
        }
        return SlowEquals(inScalar);        
    }

    bool SlowEquals(const MushcoreScalar& inScalar) const;

    MushcoreScalar& operator=(const std::string &inStr)
    {
        m_string=inStr;
        m_tag=kString;
        return *this;
    }
    MushcoreScalar& operator=(Mushware::tVal inVal)
    {
        m_val=inVal;
        m_tag=kVal;
        return *this;
    }

    // Conversion operators
    // operator Mushware::tVal() const { return Val(); }
    // operator std::string() const { return String(); }
    
    void ostreamPrint(std::ostream &inOut) const;

private:
    enum Tag
    {
        kNone,
        kVal,
        kString
    };
    Tag m_tag;
    Mushware::tVal m_val;
    std::string m_string;
};

inline bool operator==(const MushcoreScalar& a, const MushcoreScalar& b)
{
    return a.Equals(b);
}

inline bool operator!=(const MushcoreScalar& a, const MushcoreScalar& b)
{
    return !a.Equals(b);
}

inline std::ostream& operator<<(std::ostream& inOut, const MushcoreScalar& inScalar)
{
    inScalar.ostreamPrint(inOut);
    return inOut;
}
#endif
#endif
