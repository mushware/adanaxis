/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class MediaNetLink;

class MediaNetWebRouter
{
public:
    static MediaNetWebRouter& Instance(void);
    void ReceiveAll(void);

protected:
    MediaNetWebRouter();

private:
    enum
    {
        kTickPeriod=100
    };

    U32 m_lastTickMsec;

    static auto_ptr<MediaNetWebRouter> m_instance;
};

inline  MediaNetWebRouter&
MediaNetWebRouter::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MediaNetWebRouter);
    return *m_instance;
}
