//%includeGuardStart {
#ifndef GLTEXTURECLIP_H
#define GLTEXTURECLIP_H
//%includeGuardStart } re2veNlOlv6w2preVbD7rg
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureClip.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } hY3meftZSqk1PaqQY9jprg
/*
 * $Id: GLTextureClip.h,v 1.12 2006/06/01 15:38:53 southa Exp $
 * $Log: GLTextureClip.h,v $
 * Revision 1.12  2006/06/01 15:38:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.10  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.9  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:30  southa
 * Fixed file headers
 *
 * Revision 1.7  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/28 16:37:40  southa
 * Texture references and decomposer
 *
 */

#include "GLTexture.h"

class GLTextureClip : public GLTexture
{
public:
    GLTextureClip(const GLTexture& inTex, Mushware::U32 inX1, Mushware::U32 inY1, Mushware::U32 inX2, Mushware::U32 inY2);
    GLTextureClip *Clone(void) const {return new GLTextureClip(*this);}

protected:

private:
    const char *FiletypeName(void) const;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
