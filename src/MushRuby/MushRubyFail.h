//%includeGuardStart {
#ifndef MUSHRUBYFAIL_H
#define MUSHRUBYFAIL_H
//%includeGuardStart } mzIxmbAiLfZek9bhkqSxQw
//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyFail.h
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
//%Header } hTk4d/BuNJMOCr+nQfG6nw
/*
 * $Id$
 * $Log$
 */

#include "MushRubyStandard.h"

class MushRubyFail : public MushcoreNonFatalFail
{
public:
    MushRubyFail();
    MushRubyFail(const std::string& inMessage);
    
    static std::string ExceptionInfo(void);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
