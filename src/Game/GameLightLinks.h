/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameLightLinks
{
public:
    enum
    {
        kNumLinks=2
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
    
private:
    tLink m_links[kNumLinks];
};


