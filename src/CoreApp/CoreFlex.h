#ifndef COREFLEX_H
#define COREFLEX_H
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
 * $Id: CoreFlex.h,v 1.8 2002/12/20 13:17:33 southa Exp $
 * $Log: CoreFlex.h,v $
 * Revision 1.8  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:45  southa
 * Conditioned source
 *
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

#include "CoreScalar.h"
#include "CoreStandard.h"

class CoreFlex
{
public:
    CoreFlex(const std::string& inStr);
    int Lex(CoreScalar *outScalar, void *inPtr);
    void SetVal(const CoreScalar& inScalar) {m_scalar=inScalar;}
    
private:
    void *m_buffer_state; // Opaque to YY_BUFFER_STATE
    CoreScalar m_scalar;
    bool m_eofFound;
};
#endif
