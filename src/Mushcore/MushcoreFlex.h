//%includeGuardStart {
#ifndef MUSHCOREFLEX_H
#define MUSHCOREFLEX_H
//%includeGuardStart } KBW9trUHfsSgbhY/mcrLkQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFlex.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } wX9c0dKL1NaCSgJg9DtcPg
/*
 * $Id: MushcoreFlex.h,v 1.7 2005/07/29 08:27:47 southa Exp $
 * $Log: MushcoreFlex.h,v $
 * Revision 1.7  2005/07/29 08:27:47  southa
 * Collision work
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
    explicit MushcoreFlex(const std::string& inStr ="");
    int Lex(MushcoreScalar *outScalar, void *inPtr);
    void SetVal(const MushcoreScalar& inScalar) {m_scalar=inScalar;}
    
private:
    MUSHCORE_NOCOPY(MushcoreFlex);

    MushcoreScalar m_scalar;
    bool m_eofFound;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
