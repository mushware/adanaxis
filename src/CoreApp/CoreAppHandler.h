#ifndef COREAPPHANDLER_H
#define COREAPPHANDLER_H
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
 * $Id: CoreAppHandler.h,v 1.6 2002/08/07 13:36:44 southa Exp $
 * $Log: CoreAppHandler.h,v $
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
 * GameData and loadtilemap command
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

#include "CoreStandard.h"
#include "CoreAppSignal.h"

class CoreAppHandler
{
public:
    virtual ~CoreAppHandler() {};
    static CoreAppHandler& Instance(void) {return *((m_instance==NULL)?m_instance=new CoreAppHandler:m_instance);}
    virtual void Mutate(CoreAppHandler *inAppHandler);
    virtual void Initialise(void);
    virtual void MainLoop(void);
    virtual void Idle(void);
    virtual void Signal(const CoreAppSignal& inSignal);
    
protected:
    CoreAppHandler() {};
private:
    static CoreAppHandler *m_instance;
};
#endif
