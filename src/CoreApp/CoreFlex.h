#ifndef COREFLEX_HP
#define COREFLEX_HP
/*
 * $Id: CoreFlex.h,v 1.2 2002/03/04 22:30:49 southa Exp $
 * $Log: CoreFlex.h,v $
 * Revision 1.2  2002/03/04 22:30:49  southa
 * Interpreter work
 *
 * Revision 1.1  2002/03/02 20:35:08  southa
 * Added flex and bison parser
 *
 */

#include "CoreStandard.h"
#include "CoreScalar.h"

class CoreFlex
{
public:
    CoreFlex(const string& inStr);
    int Lex(CoreScalar *outScalar, void *inPtr);
    void SetVal(const CoreScalar& inScalar) {m_scalar=inScalar;}
    
private:
    void *m_buffer_state; // Opaque to YY_BUFFER_STATE
    CoreScalar m_scalar;
};
#endif
