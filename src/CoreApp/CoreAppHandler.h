#ifndef COREAPPHANDLER_HP
#define COREAPPHANDLER_HP
/*
 * $Id: CoreAppHandler.h,v 1.2 2002/03/21 22:07:52 southa Exp $
 * $Log: CoreAppHandler.h,v $
 * Revision 1.2  2002/03/21 22:07:52  southa
 * Initial wrangle application handler
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "CoreStandard.h"

class CoreAppHandler
{
public:
    static CoreAppHandler& Instance(void) {return *((m_instance==NULL)?m_instance=new CoreAppHandler:m_instance);}
    virtual void Mutate(CoreAppHandler *inAppHandler);
    virtual ~CoreAppHandler() {};
    virtual void Initialise(void);
    virtual void MainLoop(void);
    virtual void Idle(bool& outQuit, int& outUSleepFor);
    virtual void Display(void) {}
    virtual void Signal(U32 inSignal) {}
protected:
    CoreAppHandler() {};
private:
    static CoreAppHandler *m_instance;
};
#endif
