#ifndef GAMELIGHTLINKS_H
#define GAMELIGHTLINKS_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameLightLinks.h,v 1.5 2003/01/11 13:03:13 southa Exp $
 * $Log: GameLightLinks.h,v $
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

#include "Mushcore.h"

class GameLightLinks
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

    GameLightLinks();
    
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

inline std::ostream& operator<<(std::ostream &inOut, const GameLightLinks& inLinks)
{
    inOut << "(";
    for (Mushware::U32 i=0; i<GameLightLinks::kNumLinks; ++i)
    {
        if (inLinks.ValidGet(i))
        {
            inOut << inLinks.LinkGet(i);
        }
        if (i+1 != GameLightLinks::kNumLinks) inOut << ",";
    }
    inOut << ")";
    return inOut;
}


inline bool operator==(const GameLightLinks& a, const GameLightLinks& b)
{
    // This is a rough comparision (doesn't check valid flags) and may err on the
    // side of false negatives only
    for (Mushware::U32 i=0; i<GameLightLinks::kNumLinks; ++i)
    {
        if (a.LinkGet(i) != b.LinkGet(i)) return false;
    }
    return true;
}

inline bool operator!=(const GameLightLinks& a, const GameLightLinks& b)
{
    // This is a rough comparision (doesn't check valid flags) and may err on the
    // side of false positives only i.e. say they're not equal when they are
    for (Mushware::U32 i=0; i<GameLightLinks::kNumLinks; ++i)
    {
        if (a.LinkGet(i) != b.LinkGet(i))
        {
            return true;
        }
    }
    return false;
}
#endif
