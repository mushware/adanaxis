//%includeGuardStart {
#ifndef MUSTLWEBROUTER_H
#define MUSTLWEBROUTER_H
//%includeGuardStart } FxZ53+ahTtTM9VAZ8dj+vA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlWebRouter.h
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
//%Header } T/MUMZIDJtyEGa/03HMU4g
/*
 * $Id: MustlWebRouter.h,v 1.10 2004/01/06 20:46:52 southa Exp $
 * $Log: MustlWebRouter.h,v $
 * Revision 1.10  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.9  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:33  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
 * Revision 1.5  2002/12/29 20:30:57  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.4  2002/12/20 13:17:47  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/13 01:06:54  southa
 * Mustl work
 *
 * Revision 1.2  2002/12/12 18:38:26  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:27  southa
 * Created Mustl
 *
 * Revision 1.3  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.2  2002/11/23 17:23:45  southa
 * Sleep in setup
 *
 * Revision 1.1  2002/11/06 14:16:57  southa
 * Basic web server
 *
 */

#include "MustlStandard.h"

#include "MustlMushcore.h"

class MustlLink;

class MustlWebRouter : public MushcoreSingleton<MustlWebRouter>
{
public:
    MustlWebRouter();

    void ReceiveAll(void);

protected:

private:
    enum
    {
        kTickPeriod=100,
        kMaxReceivesPerCall=20
    };

    Mustl::tMsec m_lastTickMsec;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
