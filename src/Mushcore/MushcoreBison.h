//%includeGuardStart {
#ifndef MUSHCOREBISON_H
#define MUSHCOREBISON_H
//%includeGuardStart } XGY1wMiRY6z0Y3dicZU7Pw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreBison.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /xS9B0abPPKxSkLhcISQjg
/*
 * $Id: MushcoreBison.h,v 1.5 2003/08/21 23:09:05 southa Exp $
 * $Log: MushcoreBison.h,v $
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
    MushcoreBison(const std::string& inStr):
        m_flex(MushcoreFlex(inStr)) {}
    MushcoreBison(MushcoreFlex& inFlex): m_flex(inFlex) {}
    int Parse(MushcoreCommand& inCommand);
    MushcoreScalar Despatch(MushcoreScalar& inCommand);
    void PushParam(MushcoreScalar& inParam);
    void ClearParams(void);

    int Lex(MushcoreScalar *outScalar, void *inPtr)
        {return m_flex.Lex(outScalar, inPtr);}
    
private:
    MushcoreFlex m_flex;
    MushcoreCommand *m_command;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
