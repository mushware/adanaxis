//%includeGuardStart {
#ifndef MUSHCOREBISON_H
#define MUSHCOREBISON_H
//%includeGuardStart } XGY1wMiRY6z0Y3dicZU7Pw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreBison.h
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
//%Header } j5KDHKySvnhwMJre+nHcZA
/*
 * $Id: MushcoreBison.h,v 1.10 2006/06/01 15:39:41 southa Exp $
 * $Log: MushcoreBison.h,v $
 * Revision 1.10  2006/06/01 15:39:41  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.8  2005/05/19 13:02:14  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:05  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/13 14:32:02  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.3  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:05  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.8  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:03  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/28 13:07:03  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.1  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/03/05 22:44:45  southa
 * Changes to command handling
 *
 * Revision 1.2  2002/03/04 22:30:48  southa
 * Interpreter work
 *
 * Revision 1.1  2002/03/02 20:35:07  southa
 * Added flex and bison parser
 *
 */

#include "MushcoreFlex.h"
#include "MushcoreStandard.h"

class MushcoreCommand;
class MushcoreScalar;

class MushcoreBison
{
public:
    explicit MushcoreBison(const std::string& inStr) :
        m_flex(inStr), m_command(NULL) {}
    // MushcoreBison(MushcoreFlex& inFlex): m_flex(inFlex) {}
    int Parse(MushcoreCommand& inCommand);
    MushcoreScalar Despatch(MushcoreScalar& inCommand);
    void PushParam(MushcoreScalar& inParam);
    void ClearParams(void);

    int Lex(MushcoreScalar *outScalar, void *inPtr)
        {return m_flex.Lex(outScalar, inPtr);}
    
private:
    MUSHCORE_NOCOPY(MushcoreBison);
    MushcoreFlex m_flex;
    MushcoreCommand *m_command;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
