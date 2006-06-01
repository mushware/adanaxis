//%includeGuardStart {
#ifndef MUSHCOREAPPHANDLER_H
#define MUSHCOREAPPHANDLER_H
//%includeGuardStart } lynq8Xlgkl/Jh0MiJI5jyw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreAppHandler.h
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
//%Header } i+XL0Lx00Vu7TzgYWs51uw
/*
 * $Id: MushcoreAppHandler.h,v 1.9 2005/05/19 13:02:14 southa Exp $
 * $Log: MushcoreAppHandler.h,v $
 * Revision 1.9  2005/05/19 13:02:14  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.7  2003/10/04 12:23:08  southa
 * File renaming
 *
 * Revision 1.6  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:04  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.3  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:05  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.3  2002/05/31 15:18:15  southa
 * Keyboard reading
 *
 * Revision 1.2  2002/05/30 14:41:13  southa
 * InfernalData and loadtilemap command
 *
 * Revision 1.1  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/03/21 22:07:52  southa
 * Initial wrangle application handler
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "MushcoreStandard.h"

class MushcoreAppSignal;

class MushcoreAppHandler
{
public:
    virtual ~MushcoreAppHandler() {};
    static MushcoreAppHandler& Sgl(void) {return *((m_instance==NULL)?m_instance=new MushcoreAppHandler:m_instance);}
    virtual void Mutate(MushcoreAppHandler *inAppHandler);
    virtual void Initialise(void);
    virtual void MainLoop(void);
    virtual void Idle(void);
    virtual void Signal(const MushcoreAppSignal& inSignal);
    
protected:
    MushcoreAppHandler() {};
    
private:
    static MushcoreAppHandler *m_instance;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
