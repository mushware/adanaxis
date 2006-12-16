//%includeGuardStart {
#ifndef MUSHFILEKEYS_H
#define MUSHFILEKEYS_H
//%includeGuardStart } Fah3a+9EtNoWq6xKxazXnA
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileKeys.h
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
//%Header } 2E/GKy6tr6CafayxMUaMug
/*
 * $Id: MushFileKeys.h,v 1.1 2006/12/15 14:03:28 southa Exp $
 * $Log: MushFileKeys.h,v $
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
