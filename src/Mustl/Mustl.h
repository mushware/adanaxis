#ifndef MUSTL_H
#define MUSTL_H
/*
 * $Id: Mustl.h,v 1.5 2002/11/25 10:43:28 southa Exp $
 * $Log: Mustl.h,v $
 * Revision 1.5  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.4  2002/11/21 18:06:17  southa
 * Non-blocking network connection
 *
 * Revision 1.3  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.2  2002/11/02 11:22:51  southa
 * Simplified UDP send and receive
 *
 * Revision 1.1  2002/10/31 15:52:15  southa
 * First network code
 *
 */

#include "MustlAddress.h"
#include "MustlData.h"
#include "MustlHandler.h"
#include "MustlID.h"
#include "MustlIDNull.h"
#include "MustlIDString.h"
#include "MustlLink.h"
#include "MustlLog.h"
#include "MustlProtocol.h"
#include "MustlRouter.h"
#include "MustlServer.h"
#include "MustlUtils.h"
#include "MustlWebLink.h"
#include "MustlWebRouter.h"
#include "MustlWebServer.h"

#include "mushCore.h"
// This'll Go

class Mustl
{
public:
    static inline Mustl& Instance(void);
    ~Mustl();

protected:
    Mustl();

private:
    static auto_ptr<Mustl> m_instance;
};

inline Mustl&
Mustl::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new Mustl);
    return *m_instance;
}
#endif
