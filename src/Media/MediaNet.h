#ifndef MEDIANET_H
#define MEDIANET_H
/*
 * $Id: MediaNet.h,v 1.4 2002/11/21 18:06:17 southa Exp $
 * $Log: MediaNet.h,v $
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

#include "mushCore.h"

class MediaNet
{
public:
    static inline MediaNet& Instance(void);
    ~MediaNet();

protected:
    MediaNet();

private:
    static auto_ptr<MediaNet> m_instance;
};

inline MediaNet&
MediaNet::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MediaNet);
    return *m_instance;
}
#endif
