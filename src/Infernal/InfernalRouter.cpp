//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalRouter.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } qKNbuOQrHP2ZbsyyRWEJ4Q
/*
 * $Id: InfernalRouter.cpp,v 1.3 2003/10/07 22:40:06 southa Exp $
 * $Log: InfernalRouter.cpp,v $
 * Revision 1.3  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
 * Revision 1.2  2003/10/06 22:23:45  southa
 * Game to GameMustl move
 *
 * Revision 1.1  2003/10/04 15:32:11  southa
 * Module split
 *
 */

#include "InfernalRouter.h"

#include "InfernalData.h"
#include "InfernalMessageControlData.h"
#include "InfernalPiecePlayer.h"

#include "mushMustlGame.h"

using namespace Mushware;
using namespace std;

void
InfernalRouter::MessageHandle(MustlData& ioData, MustlLink& inLink, U32 inType)
{
    switch (inType)
    {
        case GameProtocol::kMessageTypeControlData:
            ControlDataHandle(ioData, inLink);
            break;

        default:
            GameRouter::MessageHandle(ioData, inLink, inType);
            break;
    }
}

void
InfernalRouter::ControlDataHandle(MustlData& ioData, const MustlLink& inLink)
{
    // Find object that relates to this control data

    bool discard=true;

    if (inLink.NetIDExists())
    {
        const MustlGameID& gameNetID = dynamic_cast<const MustlGameID&>(inLink.NetIDGet());
        if (gameNetID.DataRefGet().Exists())
        {
            MustlGameClient *clientDef = gameNetID.DataRefGet().Get();
            InfernalPiecePlayer *piecePlayer;
            if (InfernalData::Sgl().PlayerGet().GetIfExists(piecePlayer, clientDef->PlayerNameGet()))
            {
                InfernalMessageControlData controlData;
                controlData.Unpack(ioData);

                U32 size = controlData.DataSizeGet();
                U32 startFrame = controlData.StartFrameGet();

                for (U32 i=0; i<size; ++i)
                {
                    const InfernalMessageControlData::DataEntry& dataEntry = controlData.DataEntryGet(i);
                    piecePlayer->ControlFrameDefAdd(dataEntry.frameDef, startFrame + dataEntry.frameOffset);
                }

                discard=false;
            }
        }
    }

    if (discard)
    {
MustlLog::Sgl().NetLog() << ": Discarding ControlData for unknown target" << endl;
    }


#if 0
    MushcoreData<InfernalPiecePlayer>& playerData = InfernalData::Sgl().PlayerGet();

    if (playerData.Exists(clientName))
    {
MustlLog::Sgl().NetLog() << inLink.TCPTargetAddressGet() << ": Found player '" << clientName << "' for data" << endl;
    }
    else
    {
MustlLog::Sgl().NetLog() << inLink.TCPTargetAddressGet() << ": Didn't find player '" << clientName << "' for data" << endl;
    }
#endif
    // Apply or store the data

    // Resend object's MotionSpec to the clients as necessary
}
