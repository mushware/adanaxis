/*
 * $Id$
 * $Log$
 */

#include "GameLightLinks.h"

GameLightLinks::GameLightLinks()
{
    for (U32 i=0; i<kNumLinks; ++i)
    {
        m_links[i].valid=false;
    }
}
