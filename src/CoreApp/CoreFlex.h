#ifndef COREFLEX_H
#define COREFLEX_H
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
 * $Id: CoreFlex.h,v 1.4 2002/07/06 18:04:16 southa Exp $
 * $Log: CoreFlex.h,v $
 * Revision 1.4  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:03  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/28 13:07:04  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
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
    bool m_eofFound;
};
#endif
