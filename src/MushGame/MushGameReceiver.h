//%includeGuardStart {
#ifndef MUSHGAMERECEIVER_H
#define MUSHGAMERECEIVER_H
//%includeGuardStart } guivrlPkjjvW1opalnnA8w
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameReceiver.h
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
//%Header } uRNXfcKWU5Th1KNwjWckkw
/*
 * $Id: MushGameReceiver.h,v 1.4 2006/06/01 20:13:00 southa Exp $
 * $Log: MushGameReceiver.h,v $
 * Revision 1.4  2006/06/01 20:13:00  southa
 * Initial texture caching
 *
 * Revision 1.3  2006/06/01 15:39:26  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/20 16:14:31  southa
 * Adanaxis work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMailbox.h"
#include "MushGameMessage.h"

class MushGameLogic;

class MushGameReceiver
{
public:
	virtual ~MushGameReceiver() {}
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage) = 0;
private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
