#ifndef COREBISON_HP
#define COREBISON_HP
/*
 * $Id: CoreBison.h,v 1.1 2002/05/10 16:39:37 southa Exp $
 * $Log: CoreBison.h,v $
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
