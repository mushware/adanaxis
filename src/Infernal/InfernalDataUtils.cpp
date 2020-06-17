//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalDataUtils.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 2BrQSYpmS4T6C0ubSMXuZg
/*
 * $Id: InfernalDataUtils.cpp,v 1.6 2006/06/01 15:39:02 southa Exp $
 * $Log: InfernalDataUtils.cpp,v $
 * Revision 1.6  2006/06/01 15:39:02  southa
 * DrawArray verification and fixes
 *
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
