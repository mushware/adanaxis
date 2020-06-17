//%includeGuardStart {
#ifndef MUSHCOREREGEXP_H
#define MUSHCOREREGEXP_H
//%includeGuardStart } YQUcDvJhKlSn8BKz4ive+A
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreRegExp.h
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
//%Header } mDcd1xaATxg9WCEF/d2ecw
/*
 * $Id: MushcoreRegExp.h,v 1.11 2006/06/01 15:39:46 southa Exp $
 * $Log: MushcoreRegExp.h,v $
 * Revision 1.11  2006/06/01 15:39:46  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.9  2005/05/19 13:02:16  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:13  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:15  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.4  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.3  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.8  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.6  2002/09/01 16:29:18  southa
 * Support Redhat paths for include files
 *
 * Revision 1.5  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.1  2002/03/18 22:21:12  southa
 * Initial wrangle command
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreFail.h"

class MushcoreRegExp
{
public:
    enum
    {
        kMaxMatches = 256
    };

    typedef std::string tPattern;
    typedef std::vector<std::string> tMatches;

    inline MushcoreRegExp();
    explicit inline MushcoreRegExp(const tPattern& inPattern);
    ~MushcoreRegExp();
    
    void SearchPatternSet(const tPattern& inPattern);
    bool Search(const std::string& inString);
    bool Search(tMatches& outMatches, const std::string& inString);

private:
    MUSHCORE_NOCOPY(MushcoreRegExp);
    bool HandleReturnCode(int inRC);
        
    void *m_regExp;
};

inline
MushcoreRegExp::MushcoreRegExp() :
    m_regExp(NULL)
{
}

inline
MushcoreRegExp::MushcoreRegExp(const tPattern& inPattern) :
    m_regExp(NULL)
{
    SearchPatternSet(inPattern);
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
