#ifndef WRANGLER_H
#define WRANGLER_H
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
 * $Id: Wrangler.h,v 1.4 2002/07/06 18:04:21 southa Exp $
 * $Log: Wrangler.h,v $
 * Revision 1.4  2002/07/06 18:04:21  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:09  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.1  2002/05/10 16:40:39  southa
 * Changed .hp files to .h
 *
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
    virtual void Process(bool& outRedraw) = 0;

private:
    
};
#endif
