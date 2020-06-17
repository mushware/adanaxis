//%includeGuardStart {
#ifndef TESSERACTTRAINERAPPHANDLER_H
#define TESSERACTTRAINERAPPHANDLER_H
//%includeGuardStart } U/hH8NSIAZ2Zy4qe29coxw
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerAppHandler.h
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
//%Header } Erj+ogb96CCqKTmmVqsgtA
/*
 * $Id: TesseractTrainerAppHandler.h,v 1.5 2006/06/01 15:39:59 southa Exp $
 * $Log: TesseractTrainerAppHandler.h,v $
 * Revision 1.5  2006/06/01 15:39:59  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/06/03 13:36:44  southa
 * win32 build fixes
 *
 * Revision 1.3  2005/05/19 13:02:21  southa
 * Mac release work
 *
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
    virtual void SetupModeEnter(void);
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
