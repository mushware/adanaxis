#ifndef MUSHCOREBISON_H
#define MUSHCOREBISON_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MushcoreBison.h,v 1.2 2003/01/11 13:03:16 southa Exp $
 * $Log: MushcoreBison.h,v $
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

#include "MushcoreStandard.h"
#include "MushcoreFlex.h"

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
#endif
