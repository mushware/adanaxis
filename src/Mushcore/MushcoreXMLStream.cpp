//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLStream.cpp
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
//%Header } Gq3F+hUWege9HBwS2hLl+Q
/*
 * $Id: MushcoreXMLStream.cpp,v 1.8 2006/06/01 15:39:49 southa Exp $
 * $Log: MushcoreXMLStream.cpp,v $
 * Revision 1.8  2006/06/01 15:39:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/05/19 13:02:17  southa
 * Mac release work
 *
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

