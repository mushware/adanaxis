//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLStream.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } fZlyF8Izx+qzIkGqAGQA/w
/*
 * $Id: MushcoreXMLStream.cpp,v 1.6 2005/05/18 15:53:27 southa Exp $
 * $Log: MushcoreXMLStream.cpp,v $
 * Revision 1.6  2005/05/18 15:53:27  southa
 * Made buildable using gcc 4.0/Mac OS X 10.4
 *
 * Revision 1.5  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.4  2003/10/01 23:18:28  southa
 * XML object handling
 *
 * Revision 1.3  2003/09/29 21:48:37  southa
 * XML work
 *
 * Revision 1.2  2003/09/23 22:57:57  southa
 * XML vector handling
 *
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
 * <marklar>(<obj type="Lampshade">
 *   <bulb type="economy">
 *    <watts>
 *    	3
 *    </watts>
 *   </bulb>
 *   <height>
 *    6
 *   </height>
 *  </obj>,<obj type="Kebab">
 *   <taste type="hot">
 *    <chillipower>
 *    	3
 *    </chillipower>
 *   </taste>
 *   <size>
 *    6
 *   </size>
 *  </obj>)</marklar>
 *
 * map< map<U32, vector<U32> > > m_marklar
 *
 * <marklar>
 * [8=[9=(2,5,4),12=(6,1,2,6)]],
 * [15=[13=>(),1=(2,5,4,3)]]
 * </marklar>
 *
 */

#include "MushcoreXMLStream.h"

