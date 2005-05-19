//%includeGuardStart {
#ifndef MUSTLCONFIGDEFPASSWORD_H
#define MUSTLCONFIGDEFPASSWORD_H
//%includeGuardStart } Yt9Q0GvDgG4ttZ4LjOM3iA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefPassword.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } t82oM53vshsE3Cm7h4+18w
/*
 * $Id: MustlConfigDefPassword.h,v 1.6 2004/01/02 21:13:14 southa Exp $
 * $Log: MustlConfigDefPassword.h,v $
 * Revision 1.6  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.5  2003/10/04 12:44:36  southa
 * File renaming
 *
 * Revision 1.4  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:23  southa
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

// Password std::string input as text field (value not displayed)
class MustlConfigDefPassword : public MustlConfigDefString
{
public:
    explicit MustlConfigDefPassword(const std::string& inValue);
    virtual ~MustlConfigDefPassword();
    virtual bool FromPostRetrieve(const std::string& inName, const std::string& inData);
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName);

    static MushcoreScalar MustlConfigPassword(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    static void NullFunction(void);

private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
