//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalDataUtils.cpp
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
//%Header } ZBXbU+rU9NE4JwZj3t+t/Q
/*
 * $Id: InfernalDataUtils.cpp,v 1.5 2005/05/19 13:02:04 southa Exp $
 * $Log: InfernalDataUtils.cpp,v $
 * Revision 1.5  2005/05/19 13:02:04  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.3  2003/10/04 15:32:10  southa
 * Module split
 *
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
