#ifndef COREAPPHANDLER_H
#define COREAPPHANDLER_H
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
 * $Id: CoreAppHandler.h,v 1.8 2002/10/22 20:41:57 southa Exp $
 * $Log: CoreAppHandler.h,v $
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

#include "CoreAppSignal.h"
#include "CoreStandard.h"

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
