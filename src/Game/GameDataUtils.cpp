//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameDataUtils.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } zxiyXZx/odF8CKIt1VtQFg
/*
 * $Id: GameDataUtils.cpp,v 1.10 2003/08/21 23:08:41 southa Exp $
 * $Log: GameDataUtils.cpp,v $
 * Revision 1.10  2003/08/21 23:08:41  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/01/20 10:45:25  southa
 * Singleton tidying
 *
 * Revision 1.8  2003/01/13 14:31:57  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.7  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.6  2002/12/29 20:59:54  southa
 * More build fixes
 *
 * Revision 1.5  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:42:03  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/21 10:12:21  southa
 * Time down counter
 *
 * Revision 1.1  2002/08/10 12:34:48  southa
 * Added current dialogues
 *
 */

#include "GameDataUtils.h"

#include "GameData.h"
#include "GameSTL.h"

using namespace Mushware;
using namespace std;

void
GameDataUtils::NamedDialoguesAdd(const string& inStr)
{
    if (inStr == "") return;
    
    bool found=false;
    MushcoreRegExp regExp(inStr);
    const GameData::DialogueMap& dialogueMap(GameData::Sgl().DialogueMapGet());
    for (GameData::DialogueMapConstIterator p = dialogueMap.begin();
         p != dialogueMap.end(); ++p)
    {
        if (regExp.Search(p->first))
        {
            GameData::Sgl().CurrentDialogueAdd(p->first, *p->second);
            found=true;
        }
    }
    if (!found)
    {
        cerr << "Searched dialogues for '" << inStr << "' but found nothing" << endl;
    }
}
