//%Header {
/*****************************************************************************
 *
 * File: src/Game/InfernalFloorDesigner.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } UcJXZGX48JlWW4CYdSaQSg
/*
 * $Id: InfernalFloorDesigner.cpp,v 1.37 2003/09/17 19:40:32 southa Exp $
 * $Log: InfernalFloorDesigner.cpp,v $
 * Revision 1.37  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.36  2003/08/21 23:08:44  southa
 * Fixed file headers
 *
 * Revision 1.35  2003/01/20 10:45:26  southa
 * Singleton tidying
 *
 * Revision 1.34  2003/01/17 13:30:38  southa
 * Source conditioning and build fixes
 *
 * Revision 1.33  2003/01/13 14:31:58  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.32  2003/01/12 17:32:53  southa
 * Mushcore work
 *
 * Revision 1.31  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.30  2002/12/29 20:59:55  southa
 * More build fixes
 *
 * Revision 1.29  2002/12/20 13:17:39  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.28  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
 * Revision 1.27  2002/12/03 20:28:16  southa
 * Network, player and control work
 *
 * Revision 1.26  2002/10/22 20:42:03  southa
 * Source conditioning
 *
 * Revision 1.25  2002/10/17 15:50:59  southa
 * Config saving, pause and quit
 *
 * Revision 1.24  2002/10/15 14:02:31  southa
 * Mode changes
 *
 * Revision 1.23  2002/10/12 15:25:13  southa
 * Facet renderer
 *
 * Revision 1.22  2002/10/11 14:01:12  southa
 * Lighting work
 *
 * Revision 1.21  2002/10/08 21:44:10  southa
 * 3D maps
 *
 * Revision 1.20  2002/10/08 17:13:17  southa
 * Tiered maps
 *
 * Revision 1.19  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.18  2002/08/21 10:12:21  southa
 * Time down counter
 *
 * Revision 1.17  2002/08/19 23:11:22  southa
 * Lap and split time tweaks
 *
 * Revision 1.16  2002/08/18 12:20:40  southa
 * Movement tweaks
 *
 * Revision 1.15  2002/08/17 11:05:58  southa
 * Tweaked zoom for high frame rate
 *
 * Revision 1.14  2002/08/17 10:41:51  southa
 * Designer fixes
 *
 * Revision 1.13  2002/08/07 13:36:49  southa
 * Conditioned source
 *
 * Revision 1.12  2002/07/19 18:42:37  southa
 * Fix for middle button drags
 *
 * Revision 1.11  2002/07/16 19:30:08  southa
 * Simplistic collision checking
 *
 * Revision 1.10  2002/07/16 18:01:23  southa
 * Fixed errors
 *
 * Revision 1.9  2002/07/16 17:58:53  southa
 * Fixed error
 *
 * Revision 1.8  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 * Revision 1.7  2002/07/08 14:22:02  southa
 * Rotated desks
 *
 * Revision 1.6  2002/07/07 13:25:56  southa
 * Template designer
 *
 * Revision 1.5  2002/07/07 11:16:07  southa
 * More designer work
 *
 * Revision 1.4  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.3  2002/07/02 19:29:01  southa
 * Tidied up selection effect in designer
 *
 * Revision 1.2  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 * Revision 1.1  2002/07/02 14:27:09  southa
 * First floor map designer build
 *
 */

#include "InfernalFloorDesigner.h"

#include "GameAppHandler.h"
#include "GameControlFrameDef.h"
#include "GameController.h"
#include "InfernalData.h"
#include "InfernalMapArea.h"
#include "InfernalMapPoint.h"
#include "InfernalMotionSpec.h"
#include "GameSTL.h"
#include "InfernalView.h"

#include "mushGL.h"

using namespace Mushware;
using namespace std;

InfernalFloorDesigner::InfernalFloorDesigner():
    m_controller(NULL),
    m_tileMap(NULL),
    m_masterScale(0.05)
    {}

void
InfernalFloorDesigner::Init(void)
{
    GLAppHandler& glHandler=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl());
    m_controllerName="controller1";
    m_tileMap=InfernalData::Sgl().TileMapGet("tiles");
    m_floorMaps.push_back(InfernalData::Sgl().FloorMapGet("floor"));
    m_floorMaps.push_back(InfernalData::Sgl().FloorMapGet("floor"));
    m_floorMaps.push_back(InfernalData::Sgl().FloorMapGet("floormap-template"));
    m_floorMaps.push_back(&m_scratchArea);
    m_scratchArea=*m_floorMaps[0];
    MUSHCOREASSERT(m_tileMap != NULL);
    MUSHCOREASSERT(m_floorMaps[0] != NULL);
    InfernalData::Sgl().ControllerGetOrCreate(m_controllerName);
    m_width=glHandler.WidthGet();
    m_height=glHandler.HeightGet();
    for (U32 i=0; i<12;++i)
    {
        m_pos.push_back(GLPoint(16,16));
    }
    for (U32 i=0; i<kUndoBufferSize; ++i)
    {
        m_undoBuffer.push_back(*m_floorMaps[0]);
    }
        
    m_highlight=GLRectangle();
    m_highlightMap=0;
    m_currentMap=0;
    m_currentUndoBuffer=0;
    m_lastUndoBuffer=0;
    m_primaryButtonState=false;
    m_secondaryButtonState=false;
    m_tierFlags.resize(kNumTiers, true);
}

void
InfernalFloorDesigner::Display(void)
{
    MUSHCOREASSERT(m_currentMap < m_floorMaps.size());
    MUSHCOREASSERT(m_currentMap < m_pos.size());

    InfernalFloorMap *floorMap(m_floorMaps[m_currentMap]);
    
    // GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());

    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::IdentityPrologue();
    glEnable(GL_NORMALIZE);
    InfernalMotionSpec lookAtSpec(m_pos[m_currentMap], 0);

    InfernalMapPoint aimingPoint(GLPoint(lookAtSpec.pos / floorMap->StepGet()));

    GLState::AmbientLightSet(InfernalData::Sgl().CurrentViewGet()->AmbientLightingGet());
    GLData::Sgl().LightsGet()->AmbientLightingSet(InfernalData::Sgl().CurrentViewGet()->AmbientLightingGet());
    GLData::Sgl().LightsGet()->LightingFactorSet(InfernalData::Sgl().CurrentViewGet()->LightingFactorGet());
//GLData::Sgl().LightsGet()->InvalidateAll();
    InfernalMotionSpec lookAtPoint;
    lookAtPoint.pos=GLPoint(lookAtSpec.pos);
    lookAtPoint.angle=lookAtSpec.angle;

    GLUtils::OrthoLookAt(lookAtPoint.pos.x, lookAtPoint.pos.y, lookAtPoint.angle);
    // m_masterScale is the proportion of the longest axis of the screen
    // taken up by one map piece
    glMatrixMode(GL_PROJECTION);
    GLUtils::Scale(m_masterScale, m_masterScale, 1);
    glMatrixMode(GL_MODELVIEW);

    // Work out how many map pieces we can see in our view
    InfernalMapArea visibleArea;
    GLPoint screenRatios(GLUtils::ScreenRatiosGet());
    GLPoint screenRadius((screenRatios / 2) / floorMap->StepGet());
    tVal circleRadius=2+screenRadius.Magnitude()/m_masterScale;
    visibleArea.CircleAdd(aimingPoint, circleRadius);

    InfernalMapArea highlightArea;
    if (m_highlightMap == m_currentMap)
    {
        highlightArea.RectangleAdd(m_highlight);
    }
    floorMap->AttachTileMap(m_tileMap);
    floorMap->Render(visibleArea, highlightArea, m_tierFlags);
    
    GLUtils::IdentityEpilogue();

    GLUtils::IdentityPrologue();
    GLUtils::OrthoLookAt(lookAtPoint.pos.x, lookAtPoint.pos.y, lookAtPoint.angle);
    GLUtils::Scale(m_masterScale, m_masterScale, 1);
    glMatrixMode(GL_MODELVIEW);
    
    GLState::BlendSet(GLState::kBlendLine);
    InfernalData::Sgl().CurrentViewGet()->OverPlotGet().Render();
    InfernalData::Sgl().CurrentViewGet()->OverPlotGet().Clear();
    GLUtils::IdentityEpilogue();

    GLUtils::OrthoPrologue();
    GLState::ColourSet(1.0,1.0,0.7,0.8);
    GLUtils orthoGL;

    orthoGL.MoveToEdge(1,1);
    orthoGL.MoveRelative(-0.03,-0.03);
    {
        ostringstream message;

        for (U32 i=0; i<kNumTiers; ++i)
        {
            if (m_tierFlags[i])
            {
                message << (i+1);
            }
            else
            {
                message << " ";;
            }
        }
        
        GLString glStr(message.str(), GLFontRef("font-mono1", 0.03), 1.0);
        glStr.Render();
    }
    orthoGL.MoveToEdge(-1,1);
    orthoGL.MoveRelative(0.03,-0.03);
    {
        ostringstream message;
        message << "F" << (m_currentMap+1);
        GLString glStr(message.str(), GLFontRef("font-mono1", 0.03), -1.0);
        glStr.Render();
    }
    
    GLUtils::OrthoEpilogue();

    GLUtils::DisplayEpilogue();
}

void
InfernalFloorDesigner::Move(void)
{
    MUSHCOREASSERT(m_floorMaps.size() > 0);
    GLAppHandler& glHandler=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl());

    if (m_controller == NULL)
    {
        m_controller=InfernalData::Sgl().ControllerGet(m_controllerName);
    }
    GameControlFrameDef frameDef;
    m_controller->StateGet(frameDef, 0);
    tVal mouseX, mouseY;

    glHandler.MousePositionGet(mouseX, mouseY);
    GLPoint mousePoint(mouseX, mouseY);
    
    for (U32 i=0; i<m_floorMaps.size() && i<12 ; ++i)
    {
        if (glHandler.KeyStateGet(GLKeys::kKeyF1+i))
        {
            m_currentMap=i;
        }
    }
    if (m_currentMap >= m_floorMaps.size()) m_currentMap=m_floorMaps.size();
    
    bool primaryState(glHandler.KeyStateGet(GLKeys::kKeyMouse1));
    bool secondaryState(glHandler.KeyStateGet(GLKeys::kKeyMouse3));
    bool tertiaryState(glHandler.KeyStateGet(GLKeys::kKeyMouse2));

    // Make all maps apart from 0 and 3 read-only
    if (m_currentMap != 0 && m_currentMap != 3)
    {
        secondaryState |= primaryState;
        primaryState=false;
    }
    
    if (m_secondaryButtonState != secondaryState)
    {
        if (secondaryState)
        {
            m_downPoint=mousePoint;
        }
    }

    if (secondaryState)
    {
        GLPoint start(m_downPoint);
        GLPoint end(mousePoint);
        GLPoint selectStep(m_floorMaps[m_currentMap]->StepGet() * m_masterScale);
        // Widen selected area by half a block
        if (end.x > start.x)
        {
            //start.x-=selectStep.x/4;
            end.x+=selectStep.x/2;
        }
        else if (end.x < start.x)
        {
            start.x+=selectStep.x/2;
            //end.x-=selectStep.x/4;
        }

        if (end.y > start.y)
        {
            //start.y-=selectStep.y/4;
            end.y+=selectStep.y/2;
        }
        else if (end.y < start.y)
        {
            start.y+=selectStep.y/2;
            // end.y-=selectStep.y/4;
        }
            
        m_highlight=GLRectangle(TranslateWindowToMap(start),
                                TranslateWindowToMap(end));
        m_highlight.FixUp();
        m_highlightMap=m_currentMap;
#if 0
        cerr << "Start was " << start.x << ", " << start.y;
        cerr << ", end was " << end.x << ", " << end.y << endl;
        cerr << "Translation was " << m_highlight.xmin << ", " <<
            m_highlight.ymin << ", " <<
            m_highlight.xmax << ", " <<
            m_highlight.ymax << endl;
#endif
    }

    GLPoint delta(0,0);

    if (tertiaryState)
    {
	    delta -= GLPoint(frameDef.mouseDeltaX, frameDef.mouseDeltaY) / (m_masterScale * 500);
    }

    GLPoint stepSize=m_floorMaps[0]->StepGet();
    
    if (frameDef.LeftPressed())
    {
        delta.x = -stepSize.x;
    }
    if (frameDef.RightPressed())
    {
        delta.x = stepSize.x;
    }
    if (frameDef.UpPressed())
    {
        delta.y = stepSize.y;
    }
    if (frameDef.DownPressed())
    {
        delta.y = -stepSize.y;
    }
    m_pos[m_currentMap] += delta;


    if (glHandler.LatchedKeyStateTake('z'))
    {
        Undo();
    }

    if (glHandler.LatchedKeyStateTake('v'))
    {
        Redo();
    }

    if (glHandler.LatchedKeyStateTake('s'))
    {
        Save();
    }

    
    if (primaryState)
    {
        if (!m_primaryButtonState)
        {
            SaveForUndo();
        }
        Paste(mousePoint);
    }
    else
    {
        if (m_primaryButtonState)
        {
            m_floorMaps[m_currentMap]->LightMapInvalidate();
        }
    }        
    m_primaryButtonState = primaryState;
    m_secondaryButtonState = secondaryState;

    if (glHandler.KeyStateGet('='))
    {
        m_masterScale += (m_masterScale / 100);
    }
    if (glHandler.KeyStateGet('-'))
    {
        m_masterScale -= (m_masterScale / 100);
    }
    for (U32 i=0; i<kNumTiers; ++i)
    {
        if (glHandler.LatchedKeyStateTake('1'+i))
        {
            m_tierFlags[i] = !m_tierFlags[i];
        }
    }
    if (glHandler.LatchedKeyStateTake(','))
    {
        SaveForUndo();
        MoveTiers(1);
    }
    if (glHandler.LatchedKeyStateTake('.'))
    {
        SaveForUndo();
        MoveTiers(-1);
    }
    if (glHandler.LatchedKeyStateTake('p'))
    {
        InfernalData::Sgl().DumpAll(cerr);
    }    
}

void
InfernalFloorDesigner::Paste(const GLPoint& inDest)
{
    MUSHCOREASSERT(m_currentMap < m_floorMaps.size());
    MUSHCOREASSERT(m_highlightMap < m_floorMaps.size());
    InfernalFloorMap *srcMap;
    if (m_currentMap == m_highlightMap)
    {
        // Read from the undo buffer if we're copying back to the same map
        srcMap=&m_undoBuffer[m_lastUndoBuffer];
    }
    else
    {
        srcMap=m_floorMaps[m_highlightMap];
    }
    InfernalFloorMap *destMap=m_floorMaps[m_currentMap];
    
    GLRectangle src(m_highlight); // Source rectangle
    GLPoint destPoint(TranslateWindowToMap(inDest));
    GLRectangle dest(destPoint, destPoint+src.Size());
    GLRectangle srcClip(0, 0, srcMap->XSize(), srcMap->YSize());
    GLRectangle destClip(0, 0, destMap->XSize(), destMap->YSize());

    src.Clip(srcClip);
    dest.Clip(destClip);

    for (S32 x=0; x<src.XSize() && x<dest.XSize(); ++x)
    {
        for (S32 y=0; y<src.YSize() && y<dest.YSize(); ++y)
        {
            GLPoint offset(x,y);
            // cerr << "Copying from " << (src.MinPoint()+offset) << " to " << (dest.MinPoint()+offset) << endl;
            InfernalFloorMap::tMapVector srcVector(srcMap->ElementGet(src.MinPoint()+offset));
            InfernalFloorMap::tMapVector destVector(destMap->ElementGet(dest.MinPoint()+offset));
            for (U32 i=0; i<kNumTiers; ++i)
            {
                if (m_tierFlags[i])
                {
                    InfernalFloorMap::tMapValue value=0;
                    if (i < srcVector.size())
                    {
                        value=srcVector[i];
                    }
                    if (i >= destVector.size())
                    {
                        destVector.resize(i+1);
                    }
                    destVector[i]=value;
                }
            }
            for (U32 i=0; i<destVector.size(); ++i)
            {
                for (U32 j=i+1; j<destVector.size(); ++j)
                {
                    if (destVector[i] == destVector[j] && destVector[i] != 0)
                    {
                        cerr << "Duplicated map value " << destVector[i] << endl;
                    }
                }
            }
    
            destMap->ElementSet(dest.MinPoint()+offset, destVector);
        }
    }
}

void
InfernalFloorDesigner::MoveTiers(S32 inStep)
{
    MUSHCOREASSERT(m_currentMap < m_floorMaps.size());
    MUSHCOREASSERT(m_highlightMap < m_floorMaps.size());
    InfernalFloorMap *srcMap=m_floorMaps[m_highlightMap];
    InfernalFloorMap *destMap=m_floorMaps[m_highlightMap];

    GLRectangle src(m_highlight);
    GLRectangle dest(m_highlight);
    GLRectangle srcClip(0, 0, srcMap->XSize(), srcMap->YSize());
    GLRectangle destClip(0, 0, destMap->XSize(), destMap->YSize());

    src.Clip(srcClip);
    dest.Clip(destClip);

    for (S32 x=0; x<src.XSize() && x<dest.XSize(); ++x)
    {
        for (S32 y=0; y<src.YSize() && y<dest.YSize(); ++y)
        {
            GLPoint offset(x,y);

            InfernalFloorMap::tMapVector srcVector(srcMap->ElementGet(src.MinPoint()+offset));
            InfernalFloorMap::tMapVector destVector;
            for (U32 i=0; i<kNumTiers; ++i)
            {
                InfernalFloorMap::tMapValue value=0;
                S32 srcTier=i+inStep;
                if (srcTier >= 0 && srcTier < static_cast<S32>(srcVector.size()) && srcTier < kNumTiers)
                {
                    value=srcVector[srcTier];
                    if (value != 0)
                    {
                        if (i >= destVector.size())
                        {
                            destVector.resize(i+1,0);
                        }
                        destVector[i]=value;
                    }
                }
            }
            if (destVector.size() == 0)
            {
                destVector.resize(1,0);
            }
            destMap->ElementSet(dest.MinPoint()+offset, destVector);
        }
    }
}


void
InfernalFloorDesigner::SaveForUndo(void)
{
    m_lastUndoBuffer=m_currentUndoBuffer;
    m_undoBuffer[m_currentUndoBuffer]=*m_floorMaps[m_currentMap];
    m_lastUndoBuffer=m_currentUndoBuffer;
    m_currentUndoBuffer = (m_currentUndoBuffer+1) % kUndoBufferSize;
}

void
InfernalFloorDesigner::Undo(void)
{
    m_undoBuffer[m_currentUndoBuffer]=*m_floorMaps[m_currentMap]; // save for redo
    m_currentUndoBuffer = (m_currentUndoBuffer+kUndoBufferSize-1) % kUndoBufferSize;
    *m_floorMaps[m_currentMap]=m_undoBuffer[m_currentUndoBuffer];
}

void
InfernalFloorDesigner::Redo(void)
{
    m_currentUndoBuffer = (m_currentUndoBuffer+1) % kUndoBufferSize;
    *m_floorMaps[m_currentMap]=m_undoBuffer[m_currentUndoBuffer];
}

void
InfernalFloorDesigner::Save(void)
{
    string filename;
    const MushcoreScalar *pScalar;
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "DESIGNER_MAP_NAME"))
    {
        filename=pScalar->StringGet();
    }
    else
    {
        filename=MushcoreEnv::Sgl().VariableGet("CONTRACT_PATH").StringGet()+"/designer_map.xml";
    }
    cout << "Saving F1 buffer to file '" << filename << "'" << endl;

    ofstream outputFile(filename.c_str());
    if (!outputFile) throw(MushcoreFileFail(filename, "Could not open file"));
    time_t now(time(NULL));
    outputFile << "<!-- Map saved by designer " << ctime(&now) << " -->" << endl;
    m_floorMaps[0]->Pickle(outputFile);
}

const GLPoint
InfernalFloorDesigner::TranslateWindowToMap(const GLPoint& inPoint)
{
    MUSHCOREASSERT(m_currentMap < m_floorMaps.size());
    MUSHCOREASSERT(m_currentMap < m_pos.size());
    GLPoint outPoint;
    GLPoint mapSteps(m_floorMaps[m_currentMap]->StepGet());
    outPoint = ((inPoint/m_masterScale) + m_pos[m_currentMap]) / mapSteps;
    outPoint += GLPoint(0.5, 0.5); // Round to nearest
    outPoint.MakeInteger();
    return outPoint;
}
