/*
 * $Id: MustlWebRouter.h,v 1.3 2002/11/25 10:43:28 southa Exp $
 * $Log: MustlWebRouter.h,v $
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

#include "mushCore.h"

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

    U32 m_lastTickMsec;

    static auto_ptr<MustlWebRouter> m_instance;
};

inline  MustlWebRouter&
MustlWebRouter::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MustlWebRouter);
    return *m_instance;
}
