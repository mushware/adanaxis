#ifndef COREBISON_H
#define COREBISON_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: CoreBison.h,v 1.3 2002/06/27 12:36:03 southa Exp $
 * $Log: CoreBison.h,v $
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

#include "CoreStandard.h"
#include "CoreFlex.h"
#include "CoreScalar.h"
#include "CoreParamList.h"

class CoreCommand;

class CoreBison
{
public:
    CoreBison(const string& inStr):
        m_flex(CoreFlex(inStr)) {}
    CoreBison(CoreFlex& inFlex): m_flex(inFlex) {}
    int Parse(CoreCommand& inCommand);
    CoreScalar Despatch(CoreScalar& inCommand);
    void PushParam(CoreScalar& inParam);
    void ClearParams(void);

    int Lex(CoreScalar *outScalar, void *inPtr)
        {return m_flex.Lex(outScalar, inPtr);}
    
private:
    CoreFlex m_flex;
    CoreCommand *m_command;
};
#endif
