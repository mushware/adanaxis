//%includeGuardStart {
#ifndef MUSHCOREAUTOBOOL_H
#define MUSHCOREAUTOBOOL_H
//%includeGuardStart } Zp59GQ28qUO3RJseIUoDFA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreAutoBool.h
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
//%Header } SxwhUKBXg0MScHmyG0XT2A
/*
 * $Id: MushcoreAutoBool.h,v 1.2 2005/07/29 08:27:47 southa Exp $
 * $Log: MushcoreAutoBool.h,v $
 * Revision 1.2  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.1  2005/06/13 14:25:45  southa
 * Pipe and ordered data work
 *
 */

#include "MushcoreStandard.h"

class MushcoreAutoBool
{
public:
    MushcoreAutoBool(bool &inBool) : m_pBool(&inBool) { *m_pBool = true; }
    ~MushcoreAutoBool() { *m_pBool = false; }
private:
    MushcoreAutoBool(const MushcoreAutoBool& inBool) : m_pBool(inBool.m_pBool) {}
    const MushcoreAutoBool& operator=(MushcoreAutoBool&) { return *this; }
    
    bool *m_pBool;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
