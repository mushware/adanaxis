//%includeGuardStart {
#ifndef TESSERACTTRAINERAPPHANDLER_H
#define TESSERACTTRAINERAPPHANDLER_H
//%includeGuardStart } U/hH8NSIAZ2Zy4qe29coxw
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerAppHandler.h
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
//%Header } gGYZia3OELOmIgAy2ACquQ
/*
 * $Id: TesseractTrainerAppHandler.h,v 1.2 2005/03/13 00:34:48 southa Exp $
 * $Log: TesseractTrainerAppHandler.h,v $
 * Revision 1.2  2005/03/13 00:34:48  southa
 * Build fixes, key support and stereo
 *
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
