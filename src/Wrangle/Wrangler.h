/*
 * $Id: Wrangler.h,v 1.1 2002/05/09 17:08:08 southa Exp $
 * $Log: Wrangler.h,v $
 * Revision 1.1  2002/05/09 17:08:08  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.3  2002/05/08 16:31:21  southa
 * Created API directory
 *
 * Revision 1.2  2002/03/24 16:35:39  southa
 * Wrangler axis finder
 *
 * Revision 1.1  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 */

#include "mushCore.h"

class Wrangler
{
public:
    virtual void Process(bool& outDoQuit, bool& outRedraw) = 0;

private:
    
};
