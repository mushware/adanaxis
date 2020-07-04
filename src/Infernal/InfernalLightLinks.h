//%includeGuardStart {
#ifndef INFERNALLIGHTLINKS_H
#define INFERNALLIGHTLINKS_H
//%includeGuardStart } C6IMFSba9xE64I2zC72iuQ
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalLightLinks.h
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
//%Header } BU9qGzL+craVPTeX6It6QQ
/*
 * $Id: InfernalLightLinks.h,v 1.6 2006/06/01 15:39:03 southa Exp $
 * $Log: InfernalLightLinks.h,v $
 * Revision 1.6  2006/06/01 15:39:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:05  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/04 12:44:35  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:05  southa
 * File renaming
 *
 * Revision 1.8  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:08:47  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/12 17:32:55  southa
 * Mushcore work
 *
 * Revision 1.5  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.4  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.2  2002/10/11 14:01:13  southa
 * Lighting work
 *
 * Revision 1.1  2002/10/10 18:25:15  southa
 * Light links and test lights
 *
 */

#include "mushMushcore.h"

class InfernalLightLinks
{
public:
    enum
    {
        kNumLinks=4
    };
    class tLink
    {
    public:
        Mushware::U32 link;
        Mushware::tVal distance;
        bool valid;
    };

    InfernalLightLinks();
    
    void LinkSet(Mushware::U32 inNum, Mushware::U32 inLink) { MUSHCOREASSERT(inNum < kNumLinks); m_links[inNum].link = inLink; }
    Mushware::U32 LinkGet(Mushware::U32 inNum) const { MUSHCOREASSERT(inNum < kNumLinks); return m_links[inNum].link; }
    void DistanceSet(Mushware::U32 inNum, Mushware::tVal inDistance) { MUSHCOREASSERT(inNum < kNumLinks); m_links[inNum].distance = inDistance; }
    Mushware::tVal DistanceGet(Mushware::U32 inNum) const { MUSHCOREASSERT(inNum < kNumLinks); return m_links[inNum].distance; }
    void ValidSet(Mushware::U32 inNum, bool inValid) { MUSHCOREASSERT(inNum < kNumLinks); m_links[inNum].valid = inValid; }
    bool ValidGet(Mushware::U32 inNum) const { MUSHCOREASSERT(inNum < kNumLinks); return m_links[inNum].valid; }
    Mushware::U32 SizeGet(void) const { return kNumLinks; }
    void Sort(void);

private:
    tLink m_links[kNumLinks];
};

inline std::ostream& operator<<(std::ostream &inOut, const InfernalLightLinks& inLinks)
{
    inOut << "(";
    for (Mushware::U32 i=0; i<InfernalLightLinks::kNumLinks; ++i)
    {
        if (inLinks.ValidGet(i))
        {
            inOut << inLinks.LinkGet(i);
        }
        if (i+1 != InfernalLightLinks::kNumLinks) inOut << ",";
    }
    inOut << ")";
    return inOut;
}


inline bool operator==(const InfernalLightLinks& a, const InfernalLightLinks& b)
{
    // This is a rough comparision (doesn't check valid flags) and may err on the
    // side of false negatives only
    for (Mushware::U32 i=0; i<InfernalLightLinks::kNumLinks; ++i)
    {
        if (a.LinkGet(i) != b.LinkGet(i)) return false;
    }
    return true;
}

inline bool operator!=(const InfernalLightLinks& a, const InfernalLightLinks& b)
{
    // This is a rough comparision (doesn't check valid flags) and may err on the
    // side of false positives only i.e. say they're not equal when they are
    for (Mushware::U32 i=0; i<InfernalLightLinks::kNumLinks; ++i)
    {
        if (a.LinkGet(i) != b.LinkGet(i))
        {
            return true;
        }
    }
    return false;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
