//%includeGuardStart {
#ifndef MUSHRUBYVALUE_H
#define MUSHRUBYVALUE_H
//%includeGuardStart } NndlecmfjA46C4ZnbIqtFQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyValue.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } 5BOLwI3DhgfDHotOLswDpg
/*
 * $Id: MushRubyValue.h,v 1.14 2006/08/17 08:57:13 southa Exp $
 * $Log: MushRubyValue.h,v $
 * Revision 1.14  2006/08/17 08:57:13  southa
 * Event handling
 *
 * Revision 1.13  2006/07/28 11:14:30  southa
 * Records for multiple spaces
 *
 * Revision 1.12  2006/07/08 16:06:00  southa
 * Ruby menus and key handling
 *
 * Revision 1.11  2006/07/07 07:57:30  southa
 * Key translation
 *
 * Revision 1.10  2006/07/04 16:55:29  southa
 * Ruby key handling
 *
 * Revision 1.9  2006/06/27 11:58:10  southa
 * Warning fixes
 *
 * Revision 1.8  2006/06/16 01:02:34  southa
 * Ruby mesh generation
 *
 * Revision 1.7  2006/06/14 18:45:51  southa
 * Ruby mesh generation
 *
 * Revision 1.6  2006/06/14 11:20:10  southa
 * Ruby mesh generation
 *
 * Revision 1.5  2006/06/13 19:30:39  southa
 * Ruby mesh generation
 *
 * Revision 1.4  2006/06/12 11:59:40  southa
 * Ruby wrapper for MushMeshVector
 *
 * Revision 1.3  2006/06/07 12:15:20  southa
 * Grid and test textures
 *
 * Revision 1.2  2006/06/06 17:58:34  southa
 * Ruby texture definition
 *
 * Revision 1.1  2006/06/06 10:29:52  southa
 * Ruby texture definitions
 *
 */

#include "MushRubyStandard.h"

//:generate
class MushRubyValue
{
public:
	typedef std::map<MushRubyValue, MushRubyValue> tRubyHash;
	
	MushRubyValue();
	explicit MushRubyValue(Mushware::tRubyValue inValue) : m_value(inValue) {}
	explicit MushRubyValue(Mushware::U32 inValue);
    explicit MushRubyValue(Mushware::tVal inValue);
	explicit MushRubyValue(bool inValue);
	explicit MushRubyValue(const char *inValue);
    explicit MushRubyValue(const std::string& inValue);
	std::string String(void) const;
	bool IsU32(void) const;
	bool IsHash(void) const;
	bool IsArray(void) const;
	bool CanBeValVector(void) const;
	std::vector<Mushware::tVal> ValVector(void) const;
	std::vector<Mushware::U32> U32Vector(void) const;
	bool Bool(void) const;
	Mushware::U32 U32(void) const;
	Mushware::tVal Val(void) const;
	void Hash(tRubyHash& outHash) const;
	tRubyHash Hash(void) const;
	Mushware::tRubyID Symbol(void) const;
	
    bool Is(Mushware::U32& outU32) const;
    Mushware::U32 ArraySize(void) const;
    MushRubyValue ArrayEntry(Mushware::U32 inIndex) const;
    
    MushRubyValue Call(Mushware::tRubyID inID) const;
    const std::string Inspect(void) const;
    
private:
	Mushware::tRubyValue m_value; //:readwrite
//%classPrototypes {
public:
    const Mushware::tRubyValue& Value(void) const { return m_value; }
    void ValueSet(const Mushware::tRubyValue& inValue) { m_value=inValue; }
//%classPrototypes } cilEi2WX4ErxeTTCJSOTBg
};

namespace Mushware
{
	typedef MushRubyValue::tRubyHash tRubyHash;
}

inline std::ostream&
operator<<(std::ostream& ioOut, const MushRubyValue& inObj)
{
    ioOut << inObj.String();
    return ioOut;
}

inline void
operator>>(MushcoreXMLIStream& ioIn, MushRubyValue& outObj)
{
    Mushware::tRubyValue value;
    ioIn >> value; // FIXME
    outObj.ValueSet(value);
}

inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushRubyValue& inObj)
{
    ioOut << inObj.Value(); // FIXME    
    return ioOut;
}

// Comparision operator for std::map
inline bool
operator<(const MushRubyValue& inA, const MushRubyValue& inB)
{
    return inA.Value() < inB.Value();	
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
