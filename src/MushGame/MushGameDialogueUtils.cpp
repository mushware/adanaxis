//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameDialogueUtils.cpp
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
//%Header } RQQs1JsLGnc5eUT1J6jhDw
/*
 * $Id: MushGameDialogueUtils.cpp,v 1.2 2006/06/01 15:39:21 southa Exp $
 * $Log: MushGameDialogueUtils.cpp,v $
 * Revision 1.2  2006/06/01 15:39:21  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/06/14 20:39:41  southa
 * Adanaxis work
 *
 */

#include "MushGameDialogueUtils.h"

#include "API/mushGL.h"

void
MushGameDialogueUtils::NamedDialoguesAdd(
    MushcoreData<MushGameDialogue>& outDialogues,
    const std::string& inRegExp)
{
    MushcoreRegExp regExp(inRegExp);
    for (MushcoreData<GameDialogue>::tIterator p = MushcoreData<GameDialogue>::Sgl().Begin();
         p != MushcoreData<GameDialogue>::Sgl().End(); ++p)
    {
        if (regExp.Search(p->first))
        {
            outDialogues.Give(p->first, new GameDialogue(*p->second));
        }
    }   
}

void
MushGameDialogueUtils::MoveAndRender(MushcoreData<MushGameDialogue>& ioDialogues,
                                     MushGameAppHandler& inAppHandler)
{
    GLUtils::OrthoPrologue();
    
    for (MushcoreData<MushGameDialogue>::tIterator p = ioDialogues.Begin();
         p != ioDialogues.End();)
    {
        p->second->Move();
        GLUtils::PushMatrix();
        p->second->Render();
        GLUtils::PopMatrix();
        MushcoreData<MushGameDialogue>::tIterator oldP = p;
        ++p;
        if (oldP->second->ExpiredGet())
        {
            ioDialogues.Delete(oldP);
        }
    }
    
    GLUtils::OrthoEpilogue();    
}
