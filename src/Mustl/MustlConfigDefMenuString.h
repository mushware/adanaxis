//%includeGuardStart {
#ifndef MUSTLCONFIGDEFMENUSTRING_H
#define MUSTLCONFIGDEFMENUSTRING_H
//%includeGuardStart } fU0g6ilEAovZfCAubGA6wQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefMenuString.h
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
//%Header } 7ay2i1OKrnk74m7xKqzmKQ
/*
 * $Id: MustlConfigDefMenuString.h,v 1.6 2005/05/19 13:02:18 southa Exp $
 * $Log: MustlConfigDefMenuString.h,v $
 * Revision 1.6  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:22  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.1  2003/01/14 12:40:10  southa
 * Moved ConfigDefs into Mustl
 *
 */

#include "MustlConfigDef.h"
#include "MustlConfigDefString.h"
#include "MustlStandard.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

// String selected from a menu
class MustlConfigDefMenuString : public MustlConfigDefString
{
public:
    explicit MustlConfigDefMenuString(const std::string& inValue, const std::string& inMenu="");
    virtual ~MustlConfigDefMenuString();
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName);

    static MushcoreScalar MustlConfigMenuString(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    static void NullFunction(void);

private:
std::string m_menu;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
