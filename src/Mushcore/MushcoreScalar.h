//%includeGuardStart {
#ifndef MUSHCORESCALAR_H
#define MUSHCORESCALAR_H
//%includeGuardStart } vUcjA4mxZjGXF9XP2C8K1Q
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreScalar.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } gEv/Oj2Alfhham3JwZRkdw
/*
 * $Id: MushcoreScalar.h,v 1.11 2003/10/04 12:23:09 southa Exp $
 * $Log: MushcoreScalar.h,v $
 * Revision 1.11  2003/10/04 12:23:09  southa
 * File renaming
 *
 * Revision 1.10  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:09:16  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/02/05 17:06:38  southa
 * Build fixes
 *
 * Revision 1.7  2003/02/04 00:11:05  southa
 * Build fixes
 *
 * Revision 1.6  2003/02/03 23:15:51  southa
 * Build work for Visual C++
 *
 * Revision 1.5  2003/01/20 17:03:22  southa
 * Command line expression evaluator enhancements
 *
 * Revision 1.4  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.3  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
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
 * InfernalContract and global configs added
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

#include "MushcoreFail.h"
#include "MushcoreStandard.h"

class MushcoreScalar
{
public:
    MushcoreScalar();
    explicit MushcoreScalar(Mushware::tLongVal inVal);
    explicit MushcoreScalar(const std::string& inStr);

    inline std::string StringGet(void) const;
    inline Mushware::tLongVal LongValGet(void) const;
    inline Mushware::tVal ValGet(void) const;
    inline Mushware::U32 U32Get(void) const;
    inline Mushware::S32 S32Get(void) const;
    inline bool BoolGet(void) const;

    inline const MushcoreScalar& operator=(const std::string& inStr);
    inline const MushcoreScalar& operator=(const Mushware::tLongVal inVal);
    inline const MushcoreScalar& operator+=(const MushcoreScalar& inScalar);
    inline const MushcoreScalar& operator-=(const MushcoreScalar& inScalar);
    inline const MushcoreScalar& operator*=(const MushcoreScalar& inScalar);
    inline const MushcoreScalar& operator/=(const MushcoreScalar& inScalar);

    inline bool Equals(const MushcoreScalar& inScalar) const;
    
    void Print(std::ostream &ioOut) const;

    inline void Get(MushcoreScalar& outScalar) const;
    inline void Get(Mushware::tLongVal& outVal) const;
    inline void Get(std::string& outStr) const;
    inline void Get(bool& outBool) const;
    inline void Get(Mushware::tVal& outVal) const;
    inline void Get(Mushware::U32& outU32) const;
    inline void Get(Mushware::S32& outS32) const;
    
private:
    enum eTypeTag
    {
        kTypeTagInvalid,
        kTypeTagNone,
        kTypeTagLongVal,
        kTypeTagString
    };

    bool SlowEquals(const MushcoreScalar& inScalar) const;
    void ValAsStringGet(std::string& outStr) const;
    void StringAsValGet(Mushware::tLongVal& outVal) const;
    void StringAsBoolGet(bool& outBool) const;
    
    eTypeTag m_typeTag;
    Mushware::tLongVal m_longVal;
    std::string m_stringVal;
};

inline
MushcoreScalar::MushcoreScalar() :
    m_typeTag(kTypeTagNone)
{
}

inline
MushcoreScalar::MushcoreScalar(Mushware::tLongVal inLongVal) :
    m_typeTag(kTypeTagLongVal),
    m_longVal(inLongVal)
{
}

inline
MushcoreScalar::MushcoreScalar(const std::string& inStr) :
    m_typeTag(kTypeTagString),
    m_stringVal(inStr)
{
}

inline std::string
MushcoreScalar::StringGet(void) const
{
    if (m_typeTag == kTypeTagString)
    {
        return m_stringVal;
    }
    std::string retStr;
    Get(retStr);
    return retStr;
}

inline Mushware::tLongVal
MushcoreScalar::LongValGet(void) const
{
    if (m_typeTag == kTypeTagLongVal)
    {
        return m_longVal;
    }
    Mushware::tLongVal retVal;
    Get(retVal);
    return retVal;
}

inline Mushware::tVal
MushcoreScalar::ValGet(void) const
{
    if (m_typeTag == kTypeTagLongVal)
    {
        return static_cast<Mushware::tVal>(m_longVal);
    }
    Mushware::tLongVal retVal;
    Get(retVal);
    return static_cast<Mushware::tVal>(retVal);
}

inline Mushware::U32
MushcoreScalar::U32Get(void) const
{
    if (m_typeTag == kTypeTagLongVal)
    {
        return static_cast<Mushware::U32>(m_longVal);
    }
    Mushware::tLongVal retVal;
    Get(retVal);
    return static_cast<Mushware::U32>(retVal);
}

inline Mushware::S32
MushcoreScalar::S32Get(void) const
{
    if (m_typeTag == kTypeTagLongVal)
    {
        return static_cast<Mushware::S32>(m_longVal);
    }
    Mushware::tLongVal retVal;
    Get(retVal);
    return static_cast<Mushware::S32>(retVal);
}

inline bool
MushcoreScalar::BoolGet(void) const
{
    if (m_typeTag == kTypeTagLongVal)
    {
        return !(!m_longVal);
    }
    bool retVal;
    Get(retVal);
    return retVal;
}

inline void
MushcoreScalar::Get(MushcoreScalar& outScalar) const
{
    outScalar = *this;
}

inline void
MushcoreScalar::Get(Mushware::tLongVal& outVal) const
{
    switch (m_typeTag)
    {
        case kTypeTagNone:
            throw(MushcoreDataFail("Use of undefined value"));
            break;

        case kTypeTagLongVal:
            outVal=m_longVal;
            break;

        case kTypeTagString:
            StringAsValGet(outVal);
            break;

        default:
            throw(MushcoreLogicFail("MushcoreScalar value fault"));
    }
}

inline void
MushcoreScalar::Get(std::string& outStr) const
{
    switch (m_typeTag)
    {
        case kTypeTagNone:
            throw(MushcoreDataFail("Use of undefined value"));
            break;

        case kTypeTagLongVal:
            ValAsStringGet(outStr);
            break;

        case kTypeTagString:
            outStr=m_stringVal;
            break;

        default:
            throw(MushcoreLogicFail("MushcoreScalar value fault"));
    }
}

inline void
MushcoreScalar::Get(bool& outBool) const
{
    switch (m_typeTag)
    {
        case kTypeTagNone:
            throw(MushcoreDataFail("Use of undefined value"));
            break;

        case kTypeTagLongVal:
            outBool=!(!m_longVal);
            break;

        case kTypeTagString:
            StringAsBoolGet(outBool);
            break;

        default:
            throw(MushcoreLogicFail("MushcoreScalar value fault"));
    }
}

inline void
MushcoreScalar::Get(Mushware::tVal& outVal) const
{
    outVal = ValGet();
}

inline void
MushcoreScalar::Get(Mushware::U32& outU32) const
{
    outU32 = U32Get();
}

inline void
MushcoreScalar::Get(Mushware::S32& outS32) const
{
    outS32 = S32Get();
}

inline const MushcoreScalar&
MushcoreScalar::operator=(const std::string &inStr)
{
    m_stringVal=inStr;
    m_typeTag=kTypeTagString;
    return *this;
}

inline const MushcoreScalar&
MushcoreScalar::operator=(const Mushware::tLongVal inVal)
{
    m_longVal=inVal;
    m_typeTag=kTypeTagLongVal;
    return *this;
}

inline const MushcoreScalar&
MushcoreScalar::operator+=(const MushcoreScalar& inScalar)
{
    if (m_typeTag == kTypeTagLongVal && inScalar.m_typeTag ==  kTypeTagLongVal)
    {
        m_longVal += inScalar.ValGet();
    }
    else if (m_typeTag == kTypeTagString && inScalar.m_typeTag ==  kTypeTagString)
    {
        m_stringVal += inScalar.StringGet();
    }
    else
    {
        throw MushcoreSyntaxFail("Cannot add variables of different types");
    }
    return *this;
}

inline const MushcoreScalar&
MushcoreScalar::operator-=(const MushcoreScalar& inScalar)
{
    if (m_typeTag == kTypeTagLongVal && inScalar.m_typeTag ==  kTypeTagLongVal)
    {
        m_longVal -= inScalar.ValGet();
    }
    else
    {
        throw MushcoreSyntaxFail("Cannot subtract non-numeric variables");
    }
    return *this;
}

inline const MushcoreScalar&
MushcoreScalar::operator*=(const MushcoreScalar& inScalar)
{
    if (m_typeTag == kTypeTagLongVal && inScalar.m_typeTag ==  kTypeTagLongVal)
    {
        m_longVal *= inScalar.ValGet();
    }
    else
    {
        throw MushcoreSyntaxFail("Cannot multiply non-numeric variables");
    }
    return *this;
}

inline const MushcoreScalar&
MushcoreScalar::operator/=(const MushcoreScalar& inScalar)
{
    if (m_typeTag == kTypeTagLongVal && inScalar.m_typeTag ==  kTypeTagLongVal)
    {
        m_longVal /= inScalar.ValGet();
    }
    else
    {
        throw MushcoreSyntaxFail("Cannot divide non-numeric variables");
    }
    return *this;
}

inline const MushcoreScalar
operator+(const MushcoreScalar& a, const MushcoreScalar& b)
{
    MushcoreScalar retScalar(a);
    retScalar += b;
    return retScalar;
}

inline const MushcoreScalar
operator-(const MushcoreScalar& a, const MushcoreScalar& b)
{
    MushcoreScalar retScalar(a);
    retScalar -= b;
    return retScalar;
}

inline const MushcoreScalar
operator*(const MushcoreScalar& a, const MushcoreScalar& b)
{
    MushcoreScalar retScalar(a);
    retScalar *= b;
    return retScalar;
}

inline const MushcoreScalar
operator/(const MushcoreScalar& a, const MushcoreScalar& b)
{
    MushcoreScalar retScalar(a);
    retScalar /= b;
    return retScalar;
}

inline bool
MushcoreScalar::Equals(const MushcoreScalar& inScalar) const
{
    if (m_typeTag == kTypeTagLongVal && inScalar.m_typeTag ==  kTypeTagLongVal)
    {
        return m_longVal == inScalar.m_longVal;
    }
    else if (m_typeTag == kTypeTagString && inScalar.m_typeTag ==  kTypeTagString)
    {
        return m_stringVal == inScalar.m_stringVal;
    }
        
    return SlowEquals(inScalar);
}

inline bool
operator==(const MushcoreScalar& a, const MushcoreScalar& b)
{
    return a.Equals(b);
}

inline bool
operator!=(const MushcoreScalar& a, const MushcoreScalar& b)
{
    return !a.Equals(b);
}

inline std::ostream&
operator<<(std::ostream& ioOut, const MushcoreScalar& inScalar)
{
    inScalar.Print(ioOut);
    return ioOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
