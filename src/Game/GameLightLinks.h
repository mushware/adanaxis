#ifndef GAMELIGHTLINKS_H
#define GAMELIGHTLINKS_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameLightLinks.h,v 1.2 2002/10/11 14:01:13 southa Exp $
 * $Log: GameLightLinks.h,v $
 * Revision 1.2  2002/10/11 14:01:13  southa
 * Lighting work
 *
 * Revision 1.1  2002/10/10 18:25:15  southa
 * Light links and test lights
 *
 */

#include "mushCore.h"

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
        U32 link;
        tVal distance;
        bool valid;
    };

    GameLightLinks();
    
    void LinkSet(U32 inNum, U32 inLink) { COREASSERT(inNum < kNumLinks); m_links[inNum].link = inLink; }
    U32 LinkGet(U32 inNum) const { COREASSERT(inNum < kNumLinks); return m_links[inNum].link; }
    void DistanceSet(U32 inNum, tVal inDistance) { COREASSERT(inNum < kNumLinks); m_links[inNum].distance = inDistance; }
    tVal DistanceGet(U32 inNum) const { COREASSERT(inNum < kNumLinks); return m_links[inNum].distance; }
    void ValidSet(U32 inNum, bool inValid) { COREASSERT(inNum < kNumLinks); m_links[inNum].valid = inValid; }
    bool ValidGet(U32 inNum) const { COREASSERT(inNum < kNumLinks); return m_links[inNum].valid; }
    U32 SizeGet(void) const { return kNumLinks; }
    void Sort(void);

private:
    tLink m_links[kNumLinks];
};

inline ostream& operator<<(ostream &inOut, const GameLightLinks& inLinks)
{
    inOut << "(";
    for (U32 i=0; i<GameLightLinks::kNumLinks; ++i)
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
    for (U32 i=0; i<GameLightLinks::kNumLinks; ++i)
    {
        if (a.LinkGet(i) != b.LinkGet(i)) return false;
    }
    return true;
}

inline bool operator!=(const GameLightLinks& a, const GameLightLinks& b)
{
    // This is a rough comparision (doesn't check valid flags) and may err on the
    // side of false positives only i.e. say they're not equal when they are
    for (U32 i=0; i<GameLightLinks::kNumLinks; ++i)
    {
        if (a.LinkGet(i) != b.LinkGet(i))
        {
            return true;
        }
    }
    return false;
}
#endif
