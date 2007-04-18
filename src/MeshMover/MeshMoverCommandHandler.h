//%includeGuardStart {
#ifndef MESHMOVERCOMMANDHANDLER_H
#define MESHMOVERCOMMANDHANDLER_H
//%includeGuardStart } 1gLLi0dvti8YYY/BbmE7VQ
//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverCommandHandler.h
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
//%Header } 2kjlK+oXfecTLieQjBG7CA
/*
 * $Id: MeshMoverCommandHandler.h,v 1.5 2006/06/01 15:39:14 southa Exp $
 * $Log: MeshMoverCommandHandler.h,v $
 * Revision 1.5  2006/06/01 15:39:14  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
 */

#include "mushMushcore.h"

class MeshMoverCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar MeshMover(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
