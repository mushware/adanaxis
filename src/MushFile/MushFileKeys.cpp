//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileKeys.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } wdVBt3eyleBph99DM4VB7w
/*
 * $Id$
 * $Log$
 */

#include "MushFileKeys.h"

MUSHCORE_SINGLETON_INSTANCE(MushFileKeys);

using namespace Mushware;
using namespace std;

MushFileKeys::MushFileKeys()
{
    m_keyEntries[0] = NULL; // Add the empty key
}

bool
MushFileKeys::Lookup(const Mushware::U8 *& outpData, Mushware::U32 inID)
{
    bool retVal = false;
    
    std::map<Mushware::U32, Mushware::U8 *>::const_iterator p = m_keyEntries.find(inID);
    if (p != m_keyEntries.end())
    {
        outpData = p->second;
        retVal = true;
    }
    
    return retVal;
}

void
MushFileKeys::KeyEntryAdd(Mushware::U32 inID, Mushware::U8 *inpData)
{
    if (m_keyEntries.find(inID) == m_keyEntries.end())
    {
        MushcoreLog::Sgl().WarningLog() << "Replacing file key " << inID << endl;
    }
    m_keyEntries[inID] = inpData;
}
