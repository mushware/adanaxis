/*
 * $Id: MediaNetRouter.h,v 1.1 2002/11/04 01:02:38 southa Exp $
 * $Log: MediaNetRouter.h,v $
 * Revision 1.1  2002/11/04 01:02:38  southa
 * Link checks
 *
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
    enum
    {
        kTickPeriod=100
    };
    
    U32 m_lastTickMsec;
    
    static auto_ptr<MediaNetRouter> m_instance;
}; 

inline  MediaNetRouter&
MediaNetRouter::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MediaNetRouter);
    return *m_instance;
}
