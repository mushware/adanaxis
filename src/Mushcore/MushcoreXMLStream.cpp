//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLStream.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } gImHcvR1YijrpW2VX2rWdw
/*
 * $Id: MushcoreXMLStream.cpp,v 1.1 2003/09/21 09:51:10 southa Exp $
 * $Log: MushcoreXMLStream.cpp,v $
 * Revision 1.1  2003/09/21 09:51:10  southa
 * Stream autogenerators
 *
 */

/*
 * XML data structure
 *
 * Not every element has a name
 * Every element has a type, but the type is only reuired for polymorphic objects
 *
 * A variable must have an outer type, and may have inner types:
 * e.g. vector< map<string, U32> > : vector is outer, the rest inner
 *
 * U32 m_marklar;
 *
 * <marklar>
 *  1
 * </marklar>
 *
 * Polymorph *m_marklar;
 *
 * <marklar type="Lampshade">
 *   <bulb type="economy">
 *    <watts>
 *    	3
 *    </watts>
 *   </bulb>
 *   <height>
 *    6
 *   </height>
 * </marklar>
 *
 * vector<U32> m_marklar;
 *
 * <marklar>(3,6,2,7,6)</marklar>
 *
 * vector<Polymorph *> m_marklar
 *
 * <marklar>(<Polymorph type="Lampshade">
 *   <bulb type="economy">
 *    <watts>
 *    	3
 *    </watts>
 *   </bulb>
 *   <height>
 *    6
 *   </height>
 *  </Polymorph>,<Polymorph type="Kebab">
 *   <taste type="hot">
 *    <chillipower>
 *    	3
 *    </chillipower>
 *   </taste>
 *   <size>
 *    6
 *   </size>
 *  </Polymorph>)</marklar>
 *
 * map< map<U32, vector<U32> > > m_marklar
 *
 * <marklar>
 * [8=[9=(2,5,4),12=(6,1,2,6)]],
 * [15=[13=>(),1=(2,5,4,3)]]
 * </marklar>
 *
 *
 * <name><type>
 *  <name><type>data</type></name>
 * </name></type>
 *
 * e.g. vector< vector<Object *> > m_myVec
 *
 * <myVec><vector>
 *  <vector>
 *   <ObjectType1>
 */

#include "MushcoreXMLStream.h"

