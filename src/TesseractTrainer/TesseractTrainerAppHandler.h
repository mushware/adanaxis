//%includeGuardStart {
#ifndef TESSERACTTRAINERAPPHANDLER_H
#define TESSERACTTRAINERAPPHANDLER_H
//%includeGuardStart } U/hH8NSIAZ2Zy4qe29coxw
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerAppHandler.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } v2MyM26dfZdvOC4fLYvXRA
/*
 * $Id: TesseractTrainerAppHandler.h,v 1.1 2005/02/03 15:46:56 southa Exp $
 * $Log: TesseractTrainerAppHandler.h,v $
 * Revision 1.1  2005/02/03 15:46:56  southa
 * Quaternion work
 *
 */

#include "mushMushcore.h"
#include "mushGame.h"

class TesseractTrainerAppHandler : public GameAppHandler
{
public:
    TesseractTrainerAppHandler();
    virtual ~TesseractTrainerAppHandler();
    virtual void GameModeEnter(bool inResume);
    virtual void CurrentGameEnd(void);
    virtual void KeyboardSignal(const GLKeyboardSignal& inSignal);
protected:
    virtual void PrepareNewGame(void);

private:
    MushcoreDataRef<GameBase> m_gameRef;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
