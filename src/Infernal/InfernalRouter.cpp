//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalRouter.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } ULQKNRp9u481XreEcavcQA
/*
 * $Id: InfernalRouter.cpp,v 1.7 2006/06/01 15:39:05 southa Exp $
 * $Log: InfernalRouter.cpp,v $
 * Revision 1.7  2006/06/01 15:39:05  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:06  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 * Revision 1.4  2004/01/02 21:13:09  southa
 * Source conditioning
 *
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

#include "InfernalSTL.h"

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
