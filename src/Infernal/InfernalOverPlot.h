//%includeGuardStart {
#ifndef INFERNALOVERPLOT_H
#define INFERNALOVERPLOT_H
//%includeGuardStart } Ns+h8D7ygWPPyxSUT09t0g
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalOverPlot.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } nFmPDSeqQLfM769mY6qmsg
/*
 * $Id: InfernalOverPlot.h,v 1.3 2004/01/02 21:13:08 southa Exp $
 * $Log: InfernalOverPlot.h,v $
 * Revision 1.3  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/04 12:44:35  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:06  southa
 * File renaming
 *
 * Revision 1.8  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:08:50  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.5  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:25  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/18 11:40:35  southa
 * Overplotting and movement
 *
 */

#include "mushMushcore.h"
#include "mushGL.h"

class InfernalOverPlot
{
public:
    InfernalOverPlot() : m_numRenderables(0) {}
    ~InfernalOverPlot() { Clear(); }
    void RenderableAdd(const GLRenderable& inRenderable, const GLColour& inColour);
    void Render(void) const;
    void Clear(void);

private:
    Mushware::U32 m_numRenderables;
    std::vector<GLRenderable *> m_renderables;
    std::vector<GLColour> m_colours;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
