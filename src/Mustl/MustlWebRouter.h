//%includeGuardStart {
#ifndef MUSTLWEBROUTER_H
#define MUSTLWEBROUTER_H
//%includeGuardStart } FxZ53+ahTtTM9VAZ8dj+vA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlWebRouter.h
 *
 * Copyright Andy Southgate 2002-2004
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } MctE4hzTzbF6lbeSYcdLFg
/*
 * $Id: MustlWebRouter.h,v 1.8 2003/09/17 19:40:38 southa Exp $
 * $Log: MustlWebRouter.h,v $
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

#include "MustlMushcoreSingleton.h"

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
