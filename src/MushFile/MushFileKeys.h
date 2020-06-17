//%includeGuardStart {
#ifndef MUSHFILEKEYS_H
#define MUSHFILEKEYS_H
//%includeGuardStart } Fah3a+9EtNoWq6xKxazXnA
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileKeys.h
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
//%Header } gfkMD6iib/GU6zNzeNAUtw
/*
 * $Id: MushFileKeys.h,v 1.2 2006/12/16 10:57:23 southa Exp $
 * $Log: MushFileKeys.h,v $
 * Revision 1.2  2006/12/16 10:57:23  southa
 * Encrypted files
 *
 * Revision 1.1  2006/12/15 14:03:28  southa
 * File key handling
 *
 */

#include "MushFileStandard.h"

class MushFileKeys : public MushcoreSingleton<MushFileKeys>
{
public:
    enum
    {
        kKeySize = 65536
    };
    
    MushFileKeys();
    
    bool Lookup(const Mushware::U8 *& outpData, Mushware::U32 inID);
    bool Exists(Mushware::U32 inID);
    void KeyEntryAdd(Mushware::U32 inID, Mushware::U8 *inpData);
    
private:
    std::map<Mushware::U32, Mushware::U8 *> m_keyEntries;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
