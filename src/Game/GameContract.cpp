/*
 * $Id$
 * $Log$
 */

#include "GameContract.h"

#include "mushCore.h"
#include "mushGL.h"

#include "GameMap.h"
#include "GameGlobalConfig.h"

GameContract::GameContract(): m_state(kInit), m_gameMap(NULL)
{
    string appPath(CoreGlobalConfig::Instance().Get("APPLPATH"));
    GameGlobalConfig::Instance().Set("MAPPATH", appPath+"/../game");
}

GameContract::~GameContract()
{
    if (m_gameMap != NULL)
    {
        delete m_gameMap;
    }
}

void
GameContract::Process(bool &outDoQuit, bool &outRedraw)
{
    switch (m_state)
    {
        case kInit:
            Init();
            m_state=kRunning;
            break;

        case kRunning:
            Running(outRedraw);
            break;
    }
}

void
GameContract::Display(void)
{
    glDrawBuffer(GL_BACK);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    GLUtils::OrthoPrologue();

    glRasterPos2f(0, 0);

    glBegin(GL_TRIANGLES);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(16,0);
    glVertex2f(0,0);
    glVertex2f(0,16);
    glEnd();

    GLUtils::OrthoEpilogue();
    glutSwapBuffers();
}

void
GameContract::Init(void)
{
    m_gameMap=new GameMap;
    string inFilename(GameGlobalConfig::Instance().Get("MAPPATH"));
    inFilename+="/GameMap.xml";
    ifstream inStream(inFilename.c_str());
    if (!inStream) throw(LoaderFail(inFilename, "Could not open file"));
    CoreXML xml(inStream, inFilename);
    m_gameMap->Unpickle(xml);
    m_gameMap->Pickle(cout);
}

void
GameContract::Running(bool &outRedraw)
{
    // outRedraw=true;
}