#ifndef MUSHCOREAPP_H
#define MUSHCOREAPP_H
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
 * $Id: MushcoreApp.h,v 1.2 2003/01/11 13:03:16 southa Exp $
 * $Log: MushcoreApp.h,v $
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:05  southa
 * Created Mushcore
 *
 * Revision 1.10  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
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
 * Revision 1.4  2002/07/02 14:27:12  southa
 * First floor std::map designer build
 *
 * Revision 1.3  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/30 14:41:13  southa
 * GameData and loadtilemap command
 *
 * Revision 1.1  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.4  2002/03/07 22:24:32  southa
 * Command interpreter working
 *
 * Revision 1.3  2002/03/05 22:44:45  southa
 * Changes to command handling
 *
 * Revision 1.2  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "MushcoreCommandHandler.h"
#include "MushcoreStandard.h"

class MushcoreApp
{
public:
    
    static MushcoreApp& Instance(void) {return *((m_instance==NULL)?m_instance=new MushcoreApp:m_instance);}

protected:
    MushcoreApp() {}
    
private:
    static MushcoreApp *m_instance;
};

#endif
