//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreUtil.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } Nd4PoIz3nPwfnH84Wy1Y3w
/*
 * $Id: MushcoreUtil.cpp,v 1.18 2005/05/19 13:02:17 southa Exp $
 * $Log: MushcoreUtil.cpp,v $
 * Revision 1.18  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.17  2005/04/11 23:31:41  southa
 * Startup and registration screen
 *
 * Revision 1.16  2005/03/13 00:34:47  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.15  2004/01/18 18:25:29  southa
 * XML stream upgrades
 *
 * Revision 1.14  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.13  2003/10/04 12:23:09  southa
 * File renaming
 *
 * Revision 1.12  2003/10/02 23:33:38  southa
 * XML polymorphic objects
 *
 * Revision 1.11  2003/09/29 21:48:37  southa
 * XML work
 *
 * Revision 1.10  2003/09/24 19:03:22  southa
 * XML map IO
 *
 * Revision 1.9  2003/09/23 22:57:57  southa
 * XML vector handling
 *
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
 * InfernalContract and global configs added
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
#include "MushcoreRegExp.h"
#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

string
MushcoreUtil::TranslateFilename(const string& inStr)
{
    return inStr;
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
        else if (byte == '"')
        {
            retStr += "&quot;";
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
    while (replacePos = retStr.find("&gt;", replacePos), replacePos != string::npos)
    {
        retStr = retStr.substr(0, replacePos) + ">" + retStr.substr(replacePos + 4, string::npos);
        ++replacePos;
    }
    replacePos = 0;
    while (replacePos = retStr.find("&quot;", replacePos), replacePos != string::npos)
    {
        retStr = retStr.substr(0, replacePos) + "\"" + retStr.substr(replacePos + 6, string::npos);
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

bool
MushcoreUtil::XMLAttributeExtract(string& outTypeStr, const string& inTagData, const string& inAttrName)
{
    MushcoreRegExp regExp(inAttrName+"=\"([^\"]*)\"");
    MushcoreRegExp::tMatches matches;
    if (regExp.Search(matches, inTagData))
    {
        outTypeStr = matches[0];
        return true;
    }
    return false;
}

std::istream *
MushcoreUtil::IStringStreamNew(const std::string& inStr)
{
    return new istringstream(inStr);
}

string
MushcoreUtil::MakeXMLSafe(const string& inStr)
{
    return MakeWebSafe(inStr);
}

string
MushcoreUtil::MakeWebSafe(const string& inStr)
{
    string retStr;
    U32 size=inStr.size();
    for (U32 i=0; i<size; ++i)
    {
        U8 byte=inStr[i];
        if (byte == '"' ||
            byte == '\'')
        {
            // Discard
        }
        else if (byte < ' ')
        {
            retStr+=" ";
        }
        else if (byte == '<')
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
        else
        {
            retStr+=byte;
        }
    }
    return retStr;
}

string
MushcoreUtil::RemoveMeta(const string& inStr)
{
    string retStr;
    U32 size=inStr.size();
    for (U32 i=0; i<size; ++i)
    {
        U8 byte=inStr[i];
        if (byte == '+' || byte < ' ')
        {
            retStr+=" ";
        }
        else if (byte == '%')
        {
            if (i+2 >= size) break;
            istringstream hexStream(inStr.substr(i+1, 2));
            U32 charVal;
            hexStream >> hex >> charVal;
            if (charVal >= ' ')
            {
                retStr += charVal;
            }
            i+=2;
        }
        else
        {
            retStr+=byte;
        }
    }
    return retStr;
}

string
MushcoreUtil::InsertMeta(const string& inStr)
{
    string retStr;
    U32 size=inStr.size();
    for (U32 i=0; i<size; ++i)
    {
        U8 byte=inStr[i];
        if (byte >= ' ' && byte < '0')
        {
            retStr += "%";
            retStr += "0123456789ABCDEF"[byte / 16];
            retStr += "0123456789ABCDEF"[byte % 16];
        }
        else
        {
            retStr+=byte;
        }
    }
    return retStr;
}

std::string
MushcoreUtil::LogTimeString(void)
{
    std::time_t rawTime;
    
    std::time(&rawTime);
    std::tm *pTM = std::gmtime(&rawTime);
    
    std::ostringstream timeStream;
    timeStream << setfill('0') << setw(4) << 1900+pTM->tm_year;
    timeStream << setw(2) << pTM->tm_mon;
    timeStream << setw(2) << pTM->tm_mday;
    timeStream << "T" << setw(2) << pTM->tm_hour;
    timeStream << setw(2) << pTM->tm_min;
    timeStream << setw(2) << pTM->tm_sec;
    timeStream << "Z";
    return timeStream.str();
}

const Mushware::U32 
MushcoreUtil::RandomU32(const Mushware::U32 inMin, const Mushware::U32 inMax)
{
    return static_cast<U32>(inMin + (inMax - inMin) *((double)std::rand() / RAND_MAX));
}

void
MushcoreUtil::BreakpointFunction(void)
{
    cerr << "Hit BreakpointFuncton" << endl;
}

