/*
 * $Id$
 * $Log$
 */

#include "MediaNetRouter.h"

#include "MediaNetLink.h"
#include "MediaNetProtocol.h"

auto_ptr<MediaNetRouter> MediaNetRouter::m_instance;

MediaNetRouter::MediaNetRouter()
{
}

void
MediaNetRouter::ReceiveAll(void)
{
    CoreData<MediaNetLink>::tMapIterator endValue=CoreData<MediaNetLink>::Instance().End();
    
    for (CoreData<MediaNetLink>::tMapIterator p=CoreData<MediaNetLink>::Instance().Begin();
         p != endValue; ++p)
    {
        MediaNetData *netData=NULL;
        if (p->second->Receive(netData))
        {
            COREASSERT(netData != NULL);
            cerr << "Received on " << p->first << ": " << *netData << endl;
            U32 messageType = netData->MessageBytePop();
            if (MediaNetProtocol::MessageTypeIsLinkLayer(messageType))
            {
                cerr << "Handled at link layer" << endl;
                p->second->MessageHandle(messageType, *netData);
            }
            else
            {
                // pass to application
            }
        }
    }
}


