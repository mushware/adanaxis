//%includeGuardStart {
#ifndef GLRENDERABLE_H
#define GLRENDERABLE_H
//%includeGuardStart } pJbPZlQpqi1UWUnA/ssrzg
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLRenderable.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } B1/Pwft0I2cMLAhCLuraCw
/*
 * $Id: GLRenderable.h,v 1.9 2003/09/17 19:40:29 southa Exp $
 * $Log: GLRenderable.h,v $
 * Revision 1.9  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:27  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
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
 * InfernalDialogue added
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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
