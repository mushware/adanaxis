//%includeGuardStart {
#ifndef MUSHCOREFLEX_H
#define MUSHCOREFLEX_H
//%includeGuardStart } KBW9trUHfsSgbhY/mcrLkQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFlex.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } TgqB2YP3Vk8HqZiiUvKGCQ
/*
 * $Id: MushcoreFlex.h,v 1.4 2003/09/17 19:40:35 southa Exp $
 * $Log: MushcoreFlex.h,v $
 * Revision 1.4  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:12  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
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

#include "MushcoreScalar.h"
#include "MushcoreStandard.h"

class MushcoreFlex
{
public:
    MushcoreFlex(const std::string& inStr);
    int Lex(MushcoreScalar *outScalar, void *inPtr);
    void SetVal(const MushcoreScalar& inScalar) {m_scalar=inScalar;}
    
private:
    void *m_buffer_state; // Opaque to YY_BUFFER_STATE
    MushcoreScalar m_scalar;
    bool m_eofFound;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
