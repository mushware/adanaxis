#ifndef GLWRANGLEAPPHANDLER_H
#define GLWRANGLEAPPHANDLER_H
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
 * $Id: GLWrangleAppHandler.h,v 1.9 2002/12/20 13:17:49 southa Exp $
 * $Log: GLWrangleAppHandler.h,v $
 * Revision 1.9  2002/12/20 13:17:49  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:42:08  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 08:56:30  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:52  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:09  southa
 * Build process fixes
 *
 * Revision 1.3  2002/06/20 15:50:30  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.2  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.1  2002/05/10 16:40:39  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/09 17:08:07  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.2  2002/05/08 16:31:20  southa
 * Created API directory
 *
 * Revision 1.1  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 */


#include "Mushcore.h"
#include "mushGL.h"

class Wrangler;

class GLWrangleAppHandler : public GLUTAppHandler
{
public:
    GLWrangleAppHandler(): m_pWrangler(NULL) {}
    virtual void Initialise(void);
    virtual void Display(void);
    virtual void Idle(void);    

protected:
private:
    Wrangler *m_pWrangler;
};
#endif
