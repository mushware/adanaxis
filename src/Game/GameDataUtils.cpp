/*
 * $Id: GameDataUtils.cpp,v 1.1 2002/08/10 12:34:48 southa Exp $
 * $Log: GameDataUtils.cpp,v $
 * Revision 1.1  2002/08/10 12:34:48  southa
 * Added current dialogues
 *
 */

#include "GameDataUtils.h"

#include "GameData.h"

void
GameDataUtils::NamedDialoguesAdd(const string& inStr)
{
    if (inStr == "") return;
    
    bool found=false;
    CoreRegExp regExp(inStr);
    const GameData::DialogueMap& dialogueMap(GameData::Instance().DialogueMapGet());
    for (GameData::DialogueMapConstIterator p = dialogueMap.begin();
         p != dialogueMap.end(); ++p)
    {
        if (regExp.Search(p->first))
        {
            GameData::Instance().CurrentDialogueAdd(p->first, *p->second);
            found=true;
        }
    }
    if (!found)
    {
        cerr << "Searched dialogues for '" << inStr << "' but found nothing" << endl;
    }
}
