/*
 * $Id: GameLightLinks.cpp,v 1.1 2002/10/10 18:25:15 southa Exp $
 * $Log: GameLightLinks.cpp,v $
 * Revision 1.1  2002/10/10 18:25:15  southa
 * Light links and test lights
 *
 */

#include "GameLightLinks.h"

GameLightLinks::GameLightLinks()
{
    for (U32 i=0; i<kNumLinks; ++i)
    {
        m_links[i].valid=false;
    }
}

void
GameLightLinks::Sort(void)
{
    for (U32 i=1; i < kNumLinks; ++i)
    {
        COREASSERT(i>0);
        if (m_links[i-1].valid && m_links[i].valid)
        {
            if (m_links[i-1].link > m_links[i].link)
            {
                // Swap them
                tLink temp=m_links[i-1];
                m_links[i-1]=m_links[i];
                m_links[i]=temp;
                if (i>1)
                {
                    i-=2;
                }
                else
                {
                    i=0;
                }
            }
        }
    }
}
