#ifndef MUSHCOREAPPHANDLER_H
#define MUSHCOREAPPHANDLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MushcoreAppHandler.h,v 1.4 2003/01/20 10:45:28 southa Exp $
 * $Log: MushcoreAppHandler.h,v $
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
#endif
