//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalRouter.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } VeozmCH3dPYlaBddjtbDKw
/*
 * $Id$
 * $Log$
 */

#include "InfernalRouter.h"

#include "InfernalData.h"
#include "InfernalMessageControlData.h"
#include "InfernalPiecePlayer.h"

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
        const GameNetID& gameNetID = dynamic_cast<const GameNetID&>(inLink.NetIDGet());
        if (gameNetID.DataRefGet().Exists())
        {
            GameDefClient *clientDef = gameNetID.DataRefGet().Get();
            if (clientDef->PlayerRefGet().Exists())
            {
                InfernalPiecePlayer *piecePlayer = clientDef->PlayerRefGet().Get();

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
