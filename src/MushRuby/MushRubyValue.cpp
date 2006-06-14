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
 * $Id: MushRubyValue.cpp,v 1.5 2006/06/13 10:35:06 southa Exp $
 * $Log: MushRubyValue.cpp,v $
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

bool
MushRubyValue::Bool(void) const
{
	Mushware::tRubyValue tempValue = m_value; // Avoid const problem
	
	return (NUM2UINT(tempValue) != 0);
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
