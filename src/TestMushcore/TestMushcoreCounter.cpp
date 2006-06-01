//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreCounter.cpp
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
//%Header } ssrDQRA1N6CPpD488hxrRA
/*
 * $Id: TestMushcoreCounter.cpp,v 1.2 2005/07/29 18:51:28 southa Exp $
 * $Log: TestMushcoreCounter.cpp,v $
 * Revision 1.2  2005/07/29 18:51:28  southa
 * Maptor tweaks
 *
 * Revision 1.1  2005/06/13 14:25:46  southa
 * Pipe and ordered data work
 *
 */


#include "TestMushcoreCounter.h"

//%outOfLineFunctions {
void
TestMushcoreCounter::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    if (m_pCount == NULL)
    {
        ioOut << "pCount=NULL" ;
    }
    else
    {
        ioOut << "pCount=" << *m_pCount;
    }
    ioOut << "]";
}
//%outOfLineFunctions } QRyICuAGxR/CwyXbo+TjWA
