//%includeGuardStart {
#ifndef MUSHCOREENVOUTPUT_H
#define MUSHCOREENVOUTPUT_H
//%includeGuardStart } dRAH2I/ElRq00sHm6ljVrg
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreEnvOutput.h
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
//%Header } DtNvmsSMEPMlvyRUIk0FrQ
/*
 * $Id: MushcoreEnvOutput.h,v 1.7 2006/06/01 15:39:43 southa Exp $
 * $Log: MushcoreEnvOutput.h,v $
 * Revision 1.7  2006/06/01 15:39:43  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:11  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.2  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/11/07 11:59:02  southa
 * Web commands
 *
 */

#include "MushcoreStandard.h"

class MushcoreEnv;

class MushcoreEnvOutput
{
public:
    MushcoreEnvOutput(MushcoreEnv& inEnv, std::ostream& inOut);
    ~MushcoreEnvOutput();

private:
    MushcoreEnv& m_envRef;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
