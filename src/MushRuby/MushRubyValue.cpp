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
 * $Id$
 * $Log$
 */

#include "MushRubyValue.h"

#include "MushRubyRuby.h"

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
	else
	{
		Mushware::tRubyValue stringValue = StringValue(tempValue);
		
		retVal =  std::string(RSTRING(stringValue)->ptr, RSTRING(stringValue)->ptr + RSTRING(stringValue)->len);	
	}
	return retVal;
}
