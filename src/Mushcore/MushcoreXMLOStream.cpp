//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLOStream.cpp
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
//%Header } zEllNeAjXTTyYPzWpkfD4w
/*
 * $Id: MushcoreXMLOStream.cpp,v 1.9 2006/06/01 15:39:49 southa Exp $
 * $Log: MushcoreXMLOStream.cpp,v $
 * Revision 1.9  2006/06/01 15:39:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.6  2003/10/01 23:18:27  southa
 * XML object handling
 *
 * Revision 1.5  2003/09/22 19:40:36  southa
 * XML I/O work
 *
 * Revision 1.4  2003/09/21 11:46:11  southa
 * XML input stream
 *
 * Revision 1.3  2003/09/21 09:56:39  southa
 * Re-added
 *
 * Revision 1.1  2003/09/21 09:51:09  southa
 * Stream autogenerators
 *
 */

#include "MushcoreXMLOStream.h"

MushcoreXMLOStream::MushcoreXMLOStream(std::ostream& inStream) :
    m_pStream(inStream),
    m_tagStr("obj")
{
}
