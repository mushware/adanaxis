//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileKeys.cpp
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
//%Header } uaoEbBDZ4Xqvo8yznXMWTw
/*
 * $Id: MushFileKeys.cpp,v 1.2 2006/12/16 10:57:23 southa Exp $
 * $Log: MushFileKeys.cpp,v $
 * Revision 1.2  2006/12/16 10:57:23  southa
 * Encrypted files
 *
 * Revision 1.1  2006/12/15 14:03:28  southa
 * File key handling
 *
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

bool
MushFileKeys::Exists(Mushware::U32 inID)
{
    return m_keyEntries.find(inID) != m_keyEntries.end();
}

void
MushFileKeys::KeyEntryAdd(Mushware::U32 inID, Mushware::U8 *inpData)
{
    if (m_keyEntries.find(inID) != m_keyEntries.end())
    {
        MushcoreLog::Sgl().WarningLog() << "Replacing file key " << inID << endl;
    }
    m_keyEntries[inID] = inpData;
}
