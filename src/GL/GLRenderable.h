//%includeGuardStart {
#ifndef GLRENDERABLE_H
#define GLRENDERABLE_H
//%includeGuardStart } pJbPZlQpqi1UWUnA/ssrzg
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLRenderable.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } u5a7aDmcMTPeQgN/qzWrEg
/*
 * $Id: GLRenderable.h,v 1.13 2005/05/19 13:01:59 southa Exp $
 * $Log: GLRenderable.h,v $
 * Revision 1.13  2005/05/19 13:01:59  southa
 * Mac release work
 *
 * Revision 1.12  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.11  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.10  2003/10/04 15:32:08  southa
 * Module split
 *
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

#include "mushMushcore.h"

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
