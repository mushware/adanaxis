/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class MediaNet
{
public:
    static MediaNet& Instance(void);
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