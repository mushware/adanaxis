//%includeGuardStart {
#ifndef TESSERACTTRAINERCOMMANDHANDLER_H
#define TESSERACTTRAINERCOMMANDHANDLER_H
//%includeGuardStart } P2HcNfPJjvABO6wu045LyA
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerCommandHandler.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } eUq7/4NEsLpNlxxJCC8xRw
/*
 * $Id: TesseractTrainerCommandHandler.h,v 1.3 2006/06/01 15:39:59 southa Exp $
 * $Log: TesseractTrainerCommandHandler.h,v $
 * Revision 1.3  2006/06/01 15:39:59  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/03 15:46:57  southa
 * Quaternion work
 *
 */

#include "mushMushcore.h"

class TesseractTrainerCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar TesseractTrainer(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
