/*
 * $Id: GLWrangleAppHandler.h,v 1.2 2002/05/31 15:18:16 southa Exp $
 * $Log: GLWrangleAppHandler.h,v $
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


#include "mushCore.h"
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
