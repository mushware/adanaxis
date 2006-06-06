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
 * $Id: MushRubyValue.h,v 1.1 2006/06/06 10:29:52 southa Exp $
 * $Log: MushRubyValue.h,v $
 * Revision 1.1  2006/06/06 10:29:52  southa
 * Ruby texture definitions
 *
 */

#include "MushRubyStandard.h"

//:generate
class MushRubyValue
{
public:
	MushRubyValue();
	explicit MushRubyValue(Mushware::tRubyValue inValue) : m_value(inValue) {}
	std::string String(void) const;
	std::vector<Mushware::tVal> ValVector(void) const;
		
private:
	Mushware::tRubyValue m_value; //:read
//%classPrototypes {
public:
    const Mushware::tRubyValue& Value(void) const { return m_value; }
//%classPrototypes } 5uVSaGlp6OQXEWYc+ngbCQ
};

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

namespace Mushware
{
	typedef std::map<MushRubyValue, MushRubyValue> tRubyHash;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
