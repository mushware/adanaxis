#ifndef GLRENDERABLE_H
#define GLRENDERABLE_H
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
 * $Id: GLRenderable.h,v 1.2 2002/08/07 13:36:47 southa Exp $
 * $Log: GLRenderable.h,v $
 * Revision 1.2  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 */

class GLRenderable
{
public:
    virtual ~GLRenderable() {}
    virtual void Render(void) const = 0;
    virtual GLRenderable *Clone(void) const = 0;
};
#endif
