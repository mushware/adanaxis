//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyValue.cpp
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
//%Header } hwIlNOCEH5GsgwGY+rP1Kg
/*
 * $Id: MushRubyValue.cpp,v 1.12 2006/07/08 16:06:00 southa Exp $
 * $Log: MushRubyValue.cpp,v $
 * Revision 1.12  2006/07/08 16:06:00  southa
 * Ruby menus and key handling
 *
 * Revision 1.11  2006/07/07 07:57:29  southa
 * Key translation
 *
 * Revision 1.10  2006/07/04 16:55:28  southa
 * Ruby key handling
 *
 * Revision 1.9  2006/06/27 11:58:10  southa
 * Warning fixes
 *
 * Revision 1.8  2006/06/16 01:02:34  southa
 * Ruby mesh generation
 *
 * Revision 1.7  2006/06/14 18:45:50  southa
 * Ruby mesh generation
 *
 * Revision 1.6  2006/06/14 11:20:10  southa
 * Ruby mesh generation
 *
 * Revision 1.5  2006/06/13 10:35:06  southa
 * Ruby data objects
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

#include "MushRubyValue.h"

#include "MushRubyExec.h"
#include "MushRubyIntern.h"
#include "MushRubyRuby.h"
#include "MushRubyUtil.h"

using namespace Mushware;
using namespace std;

MushRubyValue::MushRubyValue() :
    m_value(Qnil)
{
}

MushRubyValue::MushRubyValue(Mushware::U32 inValue) :
    m_value(UINT2NUM(inValue))
{
}

MushRubyValue::MushRubyValue(Mushware::tVal inValue)
{
    m_value = rb_class_new_instance(0, 0, rb_cFloat);
    RFLOAT(m_value)->value = inValue;
}

MushRubyValue::MushRubyValue(bool inValue)
{
    if (inValue)
    {
        m_value = Qtrue;
    }
    else
    {
        m_value = Qfalse;
    }
}

MushRubyValue::MushRubyValue(const char *inValue)
{
    m_value = rb_str_new2(inValue);
}

MushRubyValue::MushRubyValue(const std::string& inValue)
{
    m_value = rb_str_new(inValue.data(), inValue.size());
}

std::string
MushRubyValue::String(void) const
{
	std::string retVal;
	
	// This doesn't detect conversion failure - just returns an empty string
	Mushware::tRubyValue tempValue = m_value; // Avoid const problem

	if (SYMBOL_P(tempValue))
	{
		retVal = std::string(rb_id2name(SYM2ID(tempValue)));
	}
	else if (rb_obj_is_instance_of(tempValue, rb_cString))
	{
		Mushware::tRubyValue stringValue = StringValue(tempValue);
		
		retVal =  std::string(RSTRING(stringValue)->ptr, RSTRING(stringValue)->ptr + RSTRING(stringValue)->len);	
	}
	else if (rb_obj_is_instance_of(tempValue, rb_cArray))
	{
		Mushware::tRubyValue stringValue = MushRubyExec::Sgl().Call(tempValue, MushRubyIntern::cToPrint());
		
		retVal = std::string(RSTRING(stringValue)->ptr, RSTRING(stringValue)->ptr + RSTRING(stringValue)->len);	
	}
	else
	{
		Mushware::tRubyValue stringValue = MushRubyExec::Sgl().Call(tempValue, MushRubyIntern::to_s());
		retVal = std::string(RSTRING(stringValue)->ptr, RSTRING(stringValue)->ptr + RSTRING(stringValue)->len);	
	}
			 
	return retVal;
}

bool
MushRubyValue::IsU32(void) const
{
	return FIXNUM_P(m_value);
}

bool
MushRubyValue::IsHash(void) const
{
	Mushware::tRubyValue tempValue = m_value; // Avoid const problem
	return rb_obj_is_instance_of(tempValue, rb_cHash);
}

bool
MushRubyValue::IsArray(void) const
{
	Mushware::tRubyValue tempValue = m_value; // Avoid const problem
	return rb_obj_is_instance_of(tempValue, rb_cArray);
}

bool
MushRubyValue::CanBeValVector(void) const
{
	Mushware::tRubyValue tempValue = m_value; // Avoid const problem
	return rb_obj_is_instance_of(tempValue, rb_cArray);
}

std::vector<Mushware::tVal>
MushRubyValue::ValVector(void) const
{
	std::vector<Mushware::tVal> retVal;
	
	Mushware::tRubyValue tempValue = m_value; // Avoid const problem
	
    if (!rb_obj_is_instance_of(tempValue, rb_cArray))
	{
		throw MushcoreDataFail("Cannot generate vector from non-array ruby type");
	}
	Mushware::tRubyValue sizeValue = MushRubyExec::Sgl().Call(tempValue, MushRubyIntern::size());
	
	for (Mushware::U32 i=0; i<NUM2UINT(sizeValue); ++i)
	{
	    retVal.push_back(NUM2DBL(rb_ary_entry(tempValue, i)));
	}
	return retVal;
}

std::vector<Mushware::U32>
MushRubyValue::U32Vector(void) const
{
	std::vector<Mushware::U32> retVal;
	
	Mushware::tRubyValue tempValue = m_value; // Avoid const problem
	
    if (!rb_obj_is_instance_of(tempValue, rb_cArray))
	{
		throw MushcoreDataFail("Cannot generate vector from non-array ruby type");
	}
	Mushware::tRubyValue sizeValue = MushRubyExec::Sgl().Call(tempValue, MushRubyIntern::size());
	
	for (Mushware::U32 i=0; i<NUM2UINT(sizeValue); ++i)
	{
	    retVal.push_back(NUM2UINT(rb_ary_entry(tempValue, i)));
	}
	return retVal;
}

bool
MushRubyValue::Bool(void) const
{
	bool retVal;
	if (m_value == Qtrue)
	{
		retVal = true;	
	}
	else if (m_value == Qfalse)
	{
		retVal = false;
	}
	else
	{
		retVal = (NUM2UINT(m_value) != 0);
	}
	return retVal;
}

Mushware::U32
MushRubyValue::U32(void) const
{
	Mushware::tRubyValue tempValue = m_value; // Avoid const problem
	
	return NUM2UINT(tempValue);
}

Mushware::tVal
MushRubyValue::Val(void) const
{
	Mushware::tRubyValue tempValue = m_value; // Avoid const problem
	
	return NUM2DBL(tempValue);
}

Mushware::tRubyHash
MushRubyValue::Hash(void) const
{
	Mushware::tRubyValue tempValue = m_value; // Avoid const problem
	
	if (!rb_obj_is_instance_of(tempValue, rb_cHash))
	{
		throw MushcoreDataFail("Cannot generate hash from non-hash ruby type");
	}
	
	Mushware::tRubyHash retHash;
	MushRubyUtil::HashConvert(retHash, tempValue);
	return retHash;
}

Mushware::tRubyID
MushRubyValue::Symbol(void) const
{
	if (!SYMBOL_P(m_value))	
	{
		throw MushcoreDataFail("Cannot generate symbol from non-symbol ruby type");
	}
	return SYM2ID(m_value);
}
