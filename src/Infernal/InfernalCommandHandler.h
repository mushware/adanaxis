//%includeGuardStart {
#ifndef INFERNALCOMMANDHANDLER_H
#define INFERNALCOMMANDHANDLER_H
//%includeGuardStart } +swOa2OZIERoGJVA5ouMHA
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalCommandHandler.h
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
//%Header } wJNHOb9STw8AyPWjSWfONA
/*
 * $Id: InfernalCommandHandler.h,v 1.5 2006/06/01 15:39:01 southa Exp $
 * $Log: InfernalCommandHandler.h,v $
 * Revision 1.5  2006/06/01 15:39:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:04  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/04 15:32:10  southa
 * Module split
 *
 */
#include "mushMushcore.h"

class InfernalCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar Infernal(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
