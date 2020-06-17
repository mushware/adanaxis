//%includeGuardStart {
#ifndef MUSHCORESTREAMUTIL_H
#define MUSHCORESTREAMUTIL_H
//%includeGuardStart } r7wM6Gh/tuQSO/Ut3wio6Q
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreStreamUtil.h
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
//%Header } bxJh4o7NOX3Gb7ZEeZzDAg
/*
 * $Id: MushcoreStreamUtil.h,v 1.9 2006/06/01 15:39:48 southa Exp $
 * $Log: MushcoreStreamUtil.h,v $
 * Revision 1.9  2006/06/01 15:39:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:16  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:13  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:18  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.3  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.6  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.2  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 09:24:10  southa
 * Name changed to MushcoreStreamUtil
 *
 * Revision 1.3  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.1  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 */

#include "MushcoreStandard.h"

class MushcoreStreamUtil
{
public:
    MushcoreStreamUtil() : m_ctr(0) {}
    Mushware::U32 BigEndianU32Get(std::istream& inIn);
    Mushware::U32 LittleEndianU32Get(std::istream& inIn);
    Mushware::U8 U8Get(std::istream& inIn);
    void Get(std::istream& inIn, Mushware::U8 *outBuffer, Mushware::U32 inSize);
    void Ignore(std::istream &inIn, Mushware::U32 inSize);
    void ZeroIndex(Mushware::U32 inWhich);
    Mushware::U32 GetIndex(Mushware::U32 inWhich);
    void ConsumeToIndex(std::istream& inIn, Mushware::U32 inWhich, Mushware::U32 inValue);
    
private:
    std::vector<int> m_zero;
    Mushware::S32 m_ctr;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
