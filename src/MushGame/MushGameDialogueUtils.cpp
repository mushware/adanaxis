//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameDialogueUtils.cpp
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
//%Header } 1dEV7DsyeK1Ck2FlsKyw8g
/*
 * $Id: MushGameDialogueUtils.cpp,v 1.5 2007/04/18 09:22:39 southa Exp $
 * $Log: MushGameDialogueUtils.cpp,v $
 * Revision 1.5  2007/04/18 09:22:39  southa
 * Header and level fixes
 *
 * Revision 1.4  2006/07/31 11:01:38  southa
 * Music and dialogues
 *
 * Revision 1.3  2006/06/30 15:05:35  southa
 * Texture and buffer purge
 *
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
    for (MushcoreData<MushGameDialogue>::tIterator p = MushcoreData<MushGameDialogue>::Sgl().Begin();
         p != MushcoreData<MushGameDialogue>::Sgl().End(); ++p)
    {
        if (regExp.Search(p->first))
        {
            outDialogues.Give(p->first, new MushGameDialogue(*p->second));
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

void
MushGameDialogueUtils::ExpireAll(MushcoreData<MushGameDialogue>& outDialogues)
{
    for (MushcoreData<MushGameDialogue>::tIterator p = outDialogues.Begin();
         p != outDialogues.End();)
    {
        p->second->ExpireNow();
    }
}
