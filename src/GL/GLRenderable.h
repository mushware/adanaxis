#ifndef GLRENDERABLE_H
#define GLRENDERABLE_H
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
 * $Id: GLRenderable.h,v 1.6 2002/12/20 13:17:35 southa Exp $
 * $Log: GLRenderable.h,v $
 * Revision 1.6  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/09 17:09:02  southa
 * GameDialogue added
 *
 * Revision 1.2  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 */

#include "Mushcore.h"

class GLRenderable
{
public:
    virtual ~GLRenderable() {}
    virtual void Render(void) const = 0;
    virtual GLRenderable *Clone(void) const = 0;
};
#endif
