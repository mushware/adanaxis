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
 * $Id: MushRubyValue.h,v 1.9 2006/06/27 11:58:10 southa Exp $
 * $Log: MushRubyValue.h,v $
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
	explicit MushRubyValue(bool inValue);
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
	tRubyHash Hash(void) const;
	Mushware::tRubyID Symbol(void) const;
	
private:
	Mushware::tRubyValue m_value; //:read
//%classPrototypes {
public:
    const Mushware::tRubyValue& Value(void) const { return m_value; }
//%classPrototypes } 5uVSaGlp6OQXEWYc+ngbCQ
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

// Comparision operator for std::map
inline bool
operator<(const MushRubyValue& inA, const MushRubyValue& inB)
{
    return inA.Value() < inB.Value();	
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
