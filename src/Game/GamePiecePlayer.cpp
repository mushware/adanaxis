/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GamePiecePlayer.cpp,v 1.27 2002/11/24 23:18:23 southa Exp $
 * $Log: GamePiecePlayer.cpp,v $
 * Revision 1.27  2002/11/24 23:18:23  southa
 * Added type name accessor to CorePickle
 *
 * Revision 1.26  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.25  2002/10/12 11:22:21  southa
 * GraphicModel work
 *
 * Revision 1.24  2002/10/08 11:58:53  southa
 * Light cache
 *
 * Revision 1.23  2002/10/07 17:49:46  southa
 * Multiple values per map element
 *
 * Revision 1.22  2002/10/07 12:15:37  southa
 * First specular lighting
 *
 * Revision 1.21  2002/08/27 08:56:25  southa
 * Source conditioning
 *
 * Revision 1.20  2002/08/20 15:00:56  southa
 * Reward tweaks
 *
 * Revision 1.19  2002/08/18 20:44:35  southa
 * Initial chequepoint work
 *
 * Revision 1.18  2002/08/18 15:13:16  southa
 * Adhesion handling
 *
 * Revision 1.17  2002/08/18 14:29:29  southa
 * More movement tweaks
 *
 * Revision 1.16  2002/08/18 12:20:40  southa
 * Movement tweaks
 *
 * Revision 1.15  2002/08/08 18:20:30  southa
 * Plot on screen of dimension 1.0
 *
 * Revision 1.14  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.13  2002/08/05 13:37:29  southa
 * Windback work
 *
 * Revision 1.12  2002/07/23 14:10:47  southa
 * Added GameMotion
 *
 * Revision 1.11  2002/07/19 15:44:41  southa
 * Graphic optimisations
 *
 * Revision 1.10  2002/07/18 13:53:48  southa
 * Tuned player motion
 *
 * Revision 1.9  2002/07/18 11:40:36  southa
 * Overplotting and movement
 *
 * Revision 1.8  2002/07/16 19:30:09  southa
 * Simplistic collision checking
 *
 * Revision 1.7  2002/07/16 17:48:08  southa
 * Collision and optimisation work
 *
 * Revision 1.6  2002/07/10 16:16:31  southa
 * Player graphic
 *
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
#include "GameView.h"
#include "GameFloorMap.h"
#include "GameSpacePoint.h"

#include "mushGL.h"

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
GamePiecePlayer::EnvironmentRead(const GameFloorMap& inFloorMap)
{
    GameSpacePoint spacePoint(m_motion.MotionSpecGet().pos);
    m_adhesion=inFloorMap.AdhesionGet(spacePoint);

    m_standingOn=inFloorMap.ElementGet(spacePoint);
}

void
GamePiecePlayer::MoveGet(GameMotionSpec& outSpec, U32 inWindbackMsec) const
{
    outSpec = m_motion.MotionSpecGet();
    // Retard the current motion
    GLPoint retardPos(outSpec.deltaPos);
    retardPos.ConstrainMagnitude(m_adhesion*m_acceleration);
    outSpec.deltaPos -= retardPos*0.5;

    // Slow down when turning
    outSpec.deltaPos /= 1+10*m_adhesion*(1-m_acceleration)*fabs(outSpec.deltaAngle);

    tVal angleRetard=outSpec.deltaAngle;
    outSpec.deltaAngle -= 0.5*m_adhesion*angleRetard;
    
    if (m_controller == NULL)
    {
        m_controller=GameData::Instance().ControllerGet(m_controllerName);
    }
    GameControllerState controlState;
    m_controller->StateGet(controlState, inWindbackMsec);
    
    outSpec.deltaAngle += m_adhesion * M_PI * controlState.mouseXDelta / 500; // Fix scaling
    tVal newAngle=outSpec.angle+outSpec.deltaAngle;

    outSpec.deltaPos.RotateAboutZ(-newAngle);
    
    GLPoint keyMovement(0,0);
    if (controlState.leftPressed)
    {
        keyMovement.x -= 1;
    }
    if (controlState.rightPressed)
    {
        keyMovement.x += 1;
    }
    if (controlState.upPressed)
    {
        keyMovement.y += 1;
    }
    if (controlState.downPressed)
    {
        keyMovement.y -= 1;
    }
    keyMovement.ConstrainMagnitude(m_adhesion*m_acceleration);

    outSpec.deltaPos += keyMovement;

    // Constrain magnitude to an egg-ellipse thing
    tVal magnitude;
    if (outSpec.deltaPos.y > 0)
    {
        magnitude=sqrt(outSpec.deltaPos.x*outSpec.deltaPos.x +
                       0.5*outSpec.deltaPos.y*outSpec.deltaPos.y);
    }
    else
    {
        magnitude=sqrt(outSpec.deltaPos.x*outSpec.deltaPos.x +
                       outSpec.deltaPos.y*outSpec.deltaPos.y);
    }
	    
    if (magnitude > m_speedLim)
    {
        // Constrain magnitude to speedLim
        outSpec.deltaPos *= m_speedLim/magnitude;
    }
    
    outSpec.deltaPos.RotateAboutZ(newAngle);
}

void
GamePiecePlayer::MoveConfirm(const GameMotionSpec& inSpec)
{
    GameMotionSpec motionSpec(inSpec);
    motionSpec.pos += motionSpec.deltaPos;
    motionSpec.angle += motionSpec.deltaAngle;
    // m_motion is the motionSpec used for windbacks
    m_motion.MotionSpecSet(motionSpec);
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
    string typeStr=inXML.GetAttribOrThrow("type").StringGet();
    GameGraphic& graphic(GameGraphic::NewFromType(typeStr));
    m_graphics.push_back(&graphic);
    graphic.Unpickle(inXML);
}

void
GamePiecePlayer::HandleMotionStart(CoreXML& inXML)
{
    m_motion.Unpickle(inXML);
}

void
GamePiecePlayer::HandleAccelerationEnd(CoreXML& inXML)
{
    istringstream inStream(inXML.TopData());
    if (!(inStream >> m_acceleration)) inXML.Throw("Expecting <acceleration>1.0</acceleration>");
}

void
GamePiecePlayer::HandleSpeedLimitEnd(CoreXML& inXML)
{
    istringstream inStream(inXML.TopData());
    if (!(inStream >> m_speedLim)) inXML.Throw("Expecting <speedlimit>0.1</speedlimit>");
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
    m_motion.Pickle(inOut, inPrefix);
    inOut << inPrefix << "<acceleration>" << m_acceleration << "</acceleration>" << endl;
    inOut << inPrefix << "<speedlimit>" << m_speedLim << "</speedlimit>" << endl;
}

void
GamePiecePlayer::UnpicklePrologue(void)
{
    GamePiece::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleInit]["player"] = &GamePiecePlayer::HandlePlayerStart;
    m_startTable[kPickleData]["name"] = &GamePiecePlayer::NullHandler;
    m_endTable[kPickleData]["name"] = &GamePiecePlayer::HandleNameEnd;
    m_startTable[kPickleData]["graphic"] = &GamePiecePlayer::HandleGraphicStart;
    m_startTable[kPickleData]["motion"] = &GamePiecePlayer::HandleMotionStart;
    m_startTable[kPickleData]["acceleration"] = &GamePiecePlayer::NullHandler;
    m_endTable[kPickleData]["acceleration"] = &GamePiecePlayer::HandleAccelerationEnd;
    m_startTable[kPickleData]["speedlimit"] = &GamePiecePlayer::NullHandler;
    m_endTable[kPickleData]["speedlimit"] = &GamePiecePlayer::HandleSpeedLimitEnd;
    m_endTable[kPickleData]["player"] = &GamePiecePlayer::HandlePlayerEnd;
    m_pickleState=kPickleInit;
    m_baseThreaded=0;
}

void
GamePiecePlayer::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    m_adhesion=0.5;
    m_acceleration=0.1;
    m_speedLim=0.1;
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

char *
GamePiecePlayer::TypeNameGet(void) const
{
    return "gamepieceplayer";
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
    GameData::Instance().TemplateDeleteAndCreate("player1", newPlayer);
    newPlayer->Unpickle(xml);
    return CoreScalar(0);
}

void
GamePiecePlayer::Install(void)
{
    CoreApp::Instance().AddHandler("loadplayer", LoadPlayer);
}
