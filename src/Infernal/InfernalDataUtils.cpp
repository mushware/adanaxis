//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalDataUtils.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } r0XbEmK9l6ohe5aiL2+V1g
/*
 * $Id: InfernalDataUtils.cpp,v 1.2 2003/10/04 12:44:34 southa Exp $
 * $Log: InfernalDataUtils.cpp,v $
 * Revision 1.2  2003/10/04 12:44:34  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:05  southa
 * File renaming
 *
 * Revision 1.11  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
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

#include "InfernalDataUtils.h"

#include "InfernalData.h"
#include "InfernalSTL.h"

using namespace Mushware;
using namespace std;

void
InfernalDataUtils::NamedDialoguesAdd(const string& inStr)
{
    if (inStr == "") return;
    
    bool found=false;
    MushcoreRegExp regExp(inStr);
    const InfernalData::DialogueMap& dialogueMap(InfernalData::Sgl().DialogueMapGet());
    for (InfernalData::DialogueMapConstIterator p = dialogueMap.begin();
         p != dialogueMap.end(); ++p)
    {
        if (regExp.Search(p->first))
        {
            InfernalData::Sgl().CurrentDialogueAdd(p->first, *p->second);
            found=true;
        }
    }
    if (!found)
    {
        cerr << "Searched dialogues for '" << inStr << "' but found nothing" << endl;
    }
}
