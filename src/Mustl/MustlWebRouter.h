#ifndef MUSTLWEBROUTER_H
#define MUSTLWEBROUTER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MustlWebRouter.h,v 1.4 2002/12/20 13:17:47 southa Exp $
 * $Log: MustlWebRouter.h,v $
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

class MustlLink;

class MustlWebRouter
{
public:
    static inline MustlWebRouter& Instance(void);
    void ReceiveAll(void);

protected:
    MustlWebRouter();

private:
    enum
    {
        kTickPeriod=100,
        kMaxReceivesPerCall=20
    };

    Mustl::tMsec m_lastTickMsec;

    static std::auto_ptr<MustlWebRouter> m_instance;
};

inline  MustlWebRouter&
MustlWebRouter::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MustlWebRouter);
    return *m_instance;
}
#endif
