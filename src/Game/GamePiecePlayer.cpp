/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: GamePiecePlayer.cpp,v 1.5 2002/07/06 18:04:19 southa Exp $
 * $Log: GamePiecePlayer.cpp,v $
 * Revision 1.5  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.3  2002/06/13 15:15:56  southa
 * New directory structure, FPS printing, load command
 *
 * Revision 1.2  2002/06/05 16:29:51  southa
 * Mouse control
 *
 * Revision 1.1  2002/06/05 15:53:26  southa
 * Player and keyboard control
 *
 */

#include "GamePiecePlayer.h"
#include "GameGraphic.h"
#include "GameData.h"
#include "GameController.h"
#include "GameGraphicSprite.h"

CoreInstaller GamePiecePlayerInstaller(GamePiecePlayer::Install);

void
GamePiecePlayer::Render(void)
{
    for (U32 i=0; i<m_graphics.size(); ++i)
    {
        m_graphics[i]->Render();
    }
}

void
GamePiecePlayer::Move(void)
{
    if (m_controller == NULL)
    {
        m_controller=GameData::Instance().ControllerGet(m_controllerName);
    }
    GameControllerState controlState;
    m_controller->StateGet(controlState);

    m_angle+=0.01*controlState.mouseXDelta;

    tVal deltaX=0;
    tVal deltaY=0;
    
    if (controlState.leftPressed)
    {
        deltaX -= cos(m_angle);
        deltaY += sin(m_angle);
    }
    if (controlState.rightPressed)
    {
        deltaX += cos(m_angle);
        deltaY -= sin(m_angle);
    }
    if (controlState.upPressed)
    {
        deltaX += sin(m_angle);
        deltaY += cos(m_angle);
    }
    if (controlState.downPressed)
    {
        deltaX -= sin(m_angle);
        deltaY -= cos(m_angle);
    }
    if (deltaX != 0 && deltaY != 0)
    {
        deltaX*=0.707;
        deltaY*=0.707;
    }
    m_x+=4*deltaX;
    m_y+=4*deltaY;
}


void
GamePiecePlayer::HandlePlayerStart(CoreXML& inXML)
{
    m_pickleState=kPickleData;
}

void
GamePiecePlayer::HandleNameEnd(CoreXML& inXML)
{
}

void
GamePiecePlayer::HandleGraphicStart(CoreXML& inXML)
{
    GameGraphicSprite *pSprite(new GameGraphicSprite);
    m_graphics.push_back(pSprite);
    pSprite->Unpickle(inXML);
}

void
GamePiecePlayer::HandlePlayerEnd(CoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GamePiecePlayer::NullHandler(CoreXML& inXML)
{
}

void
GamePiecePlayer::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<name>" << "" << "</name>" << endl;
    for (U32 i=0; i<m_graphics.size(); ++i)
    {
        inOut << inPrefix << "<graphic type=\"" << m_graphics[i]->TypeNameGet() << "\">" << endl;
        m_graphics[i]->Pickle(inOut, inPrefix+"  ");
        inOut << inPrefix << "</graphic>" << endl;
    }
}

void
GamePiecePlayer::UnpicklePrologue(void)
{
    GamePiece::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleInit]["player"] = &GamePiecePlayer::HandlePlayerStart;
    m_startTable[kPickleData]["name"] = &GamePiecePlayer::NullHandler;
    m_startTable[kPickleData]["graphic"] = &GamePiecePlayer::HandleGraphicStart;
    m_endTable[kPickleData]["name"] = &GamePiecePlayer::HandleNameEnd;
    m_endTable[kPickleData]["player"] = &GamePiecePlayer::HandlePlayerEnd;
    m_pickleState=kPickleInit;
    m_baseThreaded=0;
}

void
GamePiecePlayer::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GamePiecePlayer::UnpickleEpilogue(void)
{
    GamePiece::UnpickleEpilogue();
    m_startTable.resize(0);
    m_endTable.resize(0);
}

void
GamePiecePlayer::XMLStartHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        //        if (m_pickleState == kPickleData)
        //        {
        //            GameGraphic::XMLStartHandler(inXML);
        //            m_pickleState=kPickleWithinBase;
        //            ++m_baseThreaded;
        //        }
        //        else
        {
            ostringstream message;
            message << "Unexpected tag <" << inXML.TopTag() << "> in PiecePlayer.  Potential matches are";
            ElementFunctionMap::iterator p = m_startTable[m_pickleState].begin();
            while (p != m_startTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GamePiecePlayer::XMLEndHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        //        if (m_pickleState == kPickleWithinBase)
        //        {
        //          GameGraphic::XMLEndHandler(inXML);
        //            --m_baseThreaded;
        //            if (m_baseThreaded == 0)
        //            {
        //                m_pickleState=kPickleData;
        //            }
        //        }
        //        else
        {
            ostringstream message;
            message << "Unexpected end of tag </" << inXML.TopTag() << "> in PiecePlayer.  Potential matches are";
            ElementFunctionMap::iterator p = m_endTable[m_pickleState].begin();
            while (p != m_endTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GamePiecePlayer::XMLDataHandler(CoreXML& inXML)
{
}

CoreScalar
GamePiecePlayer::LoadPlayer(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: loadplayer <name> <filename>"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    ifstream inStream(filename.c_str());
    if (!inStream) throw(LoaderFail(filename, "Could not open file"));
    CoreXML xml(inStream, filename);
    GamePiecePlayer *newPlayer=new GamePiecePlayer;
    GameData::Instance().PieceDeleteAndCreate("player1", newPlayer);
    newPlayer->Unpickle(xml);
    return CoreScalar(0);
}

void
GamePiecePlayer::Install(void)
{
    CoreApp::Instance().AddHandler("loadplayer", LoadPlayer);
}
