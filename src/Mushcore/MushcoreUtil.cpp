//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreUtil.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } r1qdr/CPxCNbhC2AuKdGEA
/*
 * $Id: MushcoreUtil.cpp,v 1.8 2003/09/22 19:40:36 southa Exp $
 * $Log: MushcoreUtil.cpp,v $
 * Revision 1.8  2003/09/22 19:40:36  southa
 * XML I/O work
 *
 * Revision 1.7  2003/09/21 15:57:11  southa
 * XML autogenerator work
 *
 * Revision 1.6  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:19  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.3  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.2  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:08  southa
 * Created Mushcore
 *
 * Revision 1.12  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.11  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.10  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.7  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.6  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.5  2002/06/04 20:27:36  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.4  2002/05/27 12:58:43  southa
 * GameContract and global configs added
 *
 * Revision 1.3  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.1  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 */

#include "MushcoreUtil.h"
#include "MushcoreGlobalConfig.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

string
MushcoreUtil::TranslateFilename(const string& inStr)
{
    return inStr;
}

U32
MushcoreUtil::TagGet(string& outTag, const string& inStr, U32 inPos)
{
    U32 startPos = inStr.find('<', inPos);

    if (startPos == string::npos) return 0;
    U32 endPos = inStr.find('>', startPos);
    if (endPos == string::npos) return 0; // No tag end

    outTag = string(inStr, startPos+1, endPos-startPos-1);
    return endPos + 1;
}

string
MushcoreUtil::XMLMetaInsert(const string& inStr)
{
    string retStr;
    U32 size=inStr.size();
    for (U32 i=0; i<size; ++i)
    {
        U8 byte=inStr[i];

        if (byte == '<')
        {
            retStr+="&lt;";
        }
        else if (byte == '>')
        {
            retStr+="&gt;";
        }
        else if (byte == '&')
        {
            retStr+="&amp;";
        }
        else if (byte == ',')
        {
            retStr += "&#44;";
        }
        else
        {
            retStr+=byte;
        }
    }
    return retStr;
}

string
MushcoreUtil::XMLMetaRemove(const string& inStr)
{
    string retStr(inStr);
    U32 replacePos;
    replacePos = 0;
    while (replacePos = retStr.find("&lt;", replacePos), replacePos != string::npos)
    {
        retStr = retStr.substr(0, replacePos) + "<" + retStr.substr(replacePos + 4, string::npos);
        ++replacePos;
    }
    replacePos = 0;
    while (replacePos = retStr.find("&#44;", replacePos), replacePos != string::npos)
    {
        retStr = retStr.substr(0, replacePos) + "," + retStr.substr(replacePos + 5, string::npos);
        ++replacePos;
    }
    replacePos = 0;
    while (replacePos = retStr.find("&gt;", replacePos), replacePos != string::npos)
    {
        retStr = retStr.substr(0, replacePos) + ">" + retStr.substr(replacePos + 4, string::npos);
        ++replacePos;
    }
    replacePos = 0;
    while (replacePos = retStr.find("&amp;", replacePos), replacePos != string::npos)
    {
        // Ampersands last.  Tricky because of &amp;amp; possibility
        retStr = retStr.substr(0, replacePos) + "&" + retStr.substr(replacePos + 5, string::npos);
        ++replacePos;
    }
    
    return retStr;
}

std::istream *
MushcoreUtil::IStringStreamNew(const std::string& inStr)
{
    return new istringstream(inStr);
}


