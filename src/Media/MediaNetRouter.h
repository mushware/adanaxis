/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class MediaNetLink;

class MediaNetRouter
{
public:
    static MediaNetRouter& Instance(void);
    void ReceiveAll(void);

protected:
    MediaNetRouter();
    
private:
    static auto_ptr<MediaNetRouter> m_instance;
}; 

inline  MediaNetRouter&
MediaNetRouter::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MediaNetRouter);
    return *m_instance;
}
