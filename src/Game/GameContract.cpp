/*
 * $Id: GameContract.cpp,v 1.8 2002/05/31 15:18:16 southa Exp $
 * $Log: GameContract.cpp,v $
 * Revision 1.8  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.7  2002/05/30 16:21:53  southa
 * Pickleable GameContract
 *
 * Revision 1.5  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.4  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.3  2002/05/28 16:37:36  southa
 * Texture references and decomposer
 *
 * Revision 1.2  2002/05/28 13:05:55  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.1  2002/05/27 12:58:43  southa
 * GameContract and global configs added
 *
 */

#include "GameContract.h"

#include "mushCore.h"
#include "mushGL.h"

#include "GameFloorMap.h"
#include "GameData.h"
#include "GameTileMap.h"
#include "GameGlobalConfig.h"
#include "GameAppHandler.h"

CoreInstaller GameContractInstaller(GameContract::Install);

GameContract::GameContract(): m_gameState(kInit)
{
}

GameContract::~GameContract()
{
    CoreEnv::Instance().PopConfig(GameGlobalConfig::Instance());
}

void
GameContract::Process(void)
{
    switch (m_gameState)
    {
        case kInit:
            Init();
            m_gameState=kRunning;
            GLUtils::PostRedisplay();
            break;

        case kRunning:
            Running();
            break;
    }
}

void
GameContract::Display(void)
{
    switch (m_gameState)
    {
        case kInit:
            InitDisplay();
            break;
        
        case kRunning:
            RunningDisplay();
            break;
    }
}


void
GameContract::InitDisplay(void)
{
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::OrthoPrologue();
    GLUtils::RasterPos(100,100);
    GLUtils::SetColour(1,1,1);
    GLUtils::BitmapText("Loading...");
    GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
}
    
void
GameContract::RunningDisplay(void)
{
    COREASSERT(m_tileMap != NULL);
    COREASSERT(m_floorMap != NULL);
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::OrthoPrologue();

    U32 xsize=m_floorMap->XSize();
    U32 ysize=m_floorMap->YSize();
    for (U32 x=0; x<xsize; x++)
    {
        for (U32 y=0; y<ysize; y++)
        {
            U32 mapVal=m_floorMap->At(x,y);
            S32 basex=32*x;
            S32 basey=32*y;
            GLTextureRef texRef(m_tileMap->NameGet(mapVal));
            if (texRef.Exists())
            {
                GLUtils::DrawBitmap(*texRef.TextureGet(), basex, basey);
            }
        }
    }
    GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
}

void
GameContract::Init(void)
{
    m_tileMap=GameData::Instance().TileMapGet("tiles");
    m_floorMap=GameData::Instance().FloorMapGet("floor");
    COREASSERT(m_tileMap != NULL);
    COREASSERT(m_floorMap != NULL);
    m_tileMap->Load();
}

void
GameContract::Running(void)
{
    if (dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance()).KeyStateGet(GLKeys('a')))
    {
        cerr << 'a' << endl;
    }
    if (dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance()).KeyStateGet(GLKeys(GLKeys::kKeyRight)))
    {
        cerr << "(right)" << endl;
    }
    GLUtils::PostRedisplay();
    {
        static U32 frames=0;
        static U32 lastPrint=0;
        ++frames;
        U32 timeNow=glutGet(GLUT_ELAPSED_TIME);
        if (timeNow - lastPrint > 5000)
        {
            // Print FPS every 5 seconds
            cout << "FPS " << (((tVal) frames * 1000) / ((tVal) timeNow - lastPrint)) << endl;
            lastPrint=timeNow;
            frames=0;
        }
    }
        
}

void
GameContract::ScriptFunction(const string& inName) const
{
    m_script.Execute();
}

void
GameContract::NullHandler(CoreXML& inXML)
{
}

void
GameContract::HandleContractStart(CoreXML& inXML)
{
    m_pickleState=kPickleData;
}

void
GameContract::HandleContractEnd(CoreXML& inXML)
{
    inXML.Stop();
}

void
GameContract::HandleScriptStart(CoreXML& inXML)
{
}

void
GameContract::HandleScriptEnd(CoreXML& inXML)
{
    m_script=CoreScript(inXML.TopData());
}

void
GameContract::Pickle(ostream& inOut) const
{
    inOut << "<contract version=\"0.0\">" << endl;
    inOut << "<script type=\"text/core\">" << endl;
    inOut << m_script;
    inOut << "</script>" << endl;
    inOut << "</contract>";
}

void
GameContract::Unpickle(CoreXML& inXML)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleInit]["contract"] = &GameContract::HandleContractStart;
    m_startTable[kPickleData]["script"] = &GameContract::HandleScriptStart;
    m_endTable[kPickleData]["contract"] = &GameContract::HandleContractEnd;
    m_endTable[kPickleData]["script"] = &GameContract::HandleScriptEnd;

    m_pickleState=kPickleInit;
    inXML.ParseStream(*this);
}

void
GameContract::XMLStartHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << ">.  Potential matches are";
        ElementFunctionMap::iterator p = m_startTable[m_pickleState].begin();
        while (p != m_startTable[m_pickleState].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
GameContract::XMLEndHandler(CoreXML& inXML)
{
    ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << ">.  Potential matches are";
        ElementFunctionMap::iterator p = m_endTable[m_pickleState].begin();
        while (p != m_endTable[m_pickleState].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
GameContract::XMLDataHandler(CoreXML& inXML)
{
}

CoreScalar
GameContract::LoadContract(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: loadcontract <name> <filename>"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    ifstream inStream(filename.c_str());
    if (!inStream) throw(LoaderFail(filename, "Could not open file"));
    CoreXML xml(inStream, filename);
    GameData::Instance().ContractGetOrCreate(name)->Unpickle(xml);
    return CoreScalar(0);
}

void
GameContract::Install(void)
{
    CoreApp::Instance().AddHandler("loadcontract", LoadContract);
}


