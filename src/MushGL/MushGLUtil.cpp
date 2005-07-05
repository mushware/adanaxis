//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLUtil.cpp
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Hm/jgQBgeXz0hS5/I5GpkA
/*
 * $Id$
 * $Log$
 */

#include "MushGLUtil.h"

#include "API/mushPlatform.h"

using namespace Mushware;
using namespace std;

MushGLAppHandler&
MushGLUtil::AppHandler(void)
{
    MushGLAppHandler *pAppHandler=dynamic_cast<MushGLAppHandler *>(&MushcoreAppHandler::Sgl());
    if (pAppHandler == NULL)
    {
        throw MushcoreRequestFail("AppHandler of wrong type for ScreenSize");
    }
    return *pAppHandler;
}

void
MushGLUtil::IdentityPrologue(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void
MushGLUtil::IdentityEpilogue(void)
{
}

void
MushGLUtil::OrthoPrologue(void)
{
    // The screen should be enclosed by a square with corners (-0.5,-0.5) and
    // (0.5,0.5) with aspect ratio 1.  The screen is a rectangle within the square
    glMatrixMode(GL_PROJECTION);
    t2Val screenRatios(ScreenRatios()*0.5);
    gluOrtho2D(-screenRatios.X(),screenRatios.X(),-screenRatios.Y(),screenRatios.Y());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void
MushGLUtil::OrthoEpilogue(void)
{
}

void
MushGLUtil::DisplayPrologue(void)
{
    MushGLAppHandler& appHandler(AppHandler());
    switch (appHandler.CurrentModeDefGet().SyncGet())
    {
        case GLModeDef::kSyncHard:
            // glFinish();
        case GLModeDef::kSyncSoft:
            PlatformVideoUtils::VBLWait();
        default:
            appHandler.SwapBuffers();
    }
}

void
MushGLUtil::DisplayEpilogue(void)
{
    glDrawBuffer(GL_BACK);
}

void
MushGLUtil::ClearScreen(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

const t2Val
MushGLUtil::ScreenSize(void)
{
    MushGLAppHandler& appHandler(AppHandler());
    return t2Val(appHandler.ScreenWidth(), appHandler.ScreenHeight());
}

const t2Val
MushGLUtil::ScreenRatios(void)
{
    return ScreenSize() / LongestScreenAxis();
}

tVal
MushGLUtil::ScreenAspectRatio(void)
{
    t2Val screenSize(ScreenSize());
    
    return screenSize.X() / screenSize.Y();
}

tVal
MushGLUtil::LongestScreenAxis(void)
{
    t2Val screenSize(ScreenSize());
    if (screenSize.X() > screenSize.Y())
    {
        return screenSize.X();
    }
    else
    {
        return screenSize.Y();
    }
}  
