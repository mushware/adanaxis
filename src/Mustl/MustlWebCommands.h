//%includeGuardStart {
#ifndef MUSTLWEBCOMMANDS_H
#define MUSTLWEBCOMMANDS_H
//%includeGuardStart } 8zTsToM8Bq6hufrlWy88rg
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlWebCommands.h
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
//%Header } tzUfOL5rOceZT3GThGaJNg
/*
 * $Id: MustlWebCommands.h,v 1.10 2006/06/01 15:39:55 southa Exp $
 * $Log: MustlWebCommands.h,v $
 * Revision 1.10  2006/06/01 15:39:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/05/19 13:02:20  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:32  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/05/21 19:01:41  southa
 * Prerelease tweaks
 *
 * Revision 1.4  2003/04/06 12:35:23  southa
 * Fixes for release
 *
 * Revision 1.3  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.2  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.1  2003/01/14 17:38:22  southa
 * Mustl web configuration
 *
 */

#include "MustlStandard.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

class MustlWebCommands
{
public:
    static MushcoreScalar MustlPostValues(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlInputWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlServerStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlLinkStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlPrintPackageID(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlPrintMetaPackageID(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlPrintApplicationName(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void NullFunction(void);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
