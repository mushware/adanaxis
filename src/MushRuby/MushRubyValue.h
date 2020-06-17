//%includeGuardStart {
#ifndef MUSHRUBYVALUE_H
#define MUSHRUBYVALUE_H
//%includeGuardStart } NndlecmfjA46C4ZnbIqtFQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyValue.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } jb1u2RLFXe69SScBShqWqQ
/*
 * $Id: MushRubyValue.h,v 1.18 2006/11/08 18:30:54 southa Exp $
 * $Log: MushRubyValue.h,v $
 * Revision 1.18  2006/11/08 18:30:54  southa
 * Key and axis configuration
 *
 * Revision 1.17  2006/10/12 22:04:49  southa
 * Collision events
 *
 * Revision 1.16  2006/10/04 13:35:26  southa
 * Selective targetting
 *
 * Revision 1.15  2006/08/24 13:04:38  southa
 * Event handling
 *
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
	explicit MushRubyValue(Mushware::S32 inValue);
	explicit MushRubyValue(Mushware::U32 inValue);
    explicit MushRubyValue(Mushware::tVal inValue);
	explicit MushRubyValue(bool inValue);
	explicit MushRubyValue(const char *inValue);
    explicit MushRubyValue(const std::string& inValue);
	explicit MushRubyValue(const std::vector<Mushware::S32>& inVector);
	explicit MushRubyValue(const std::vector<Mushware::U32>& inVector);
	std::string String(void) const;
	bool IsNil(void) const;
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
    MushRubyValue Call(Mushware::tRubyID inID, const MushRubyValue& inParam0) const;
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
