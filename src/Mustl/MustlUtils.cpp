/*
 * $Id: MustlUtils.cpp,v 1.2 2002/12/12 18:38:25 southa Exp $
 * $Log: MustlUtils.cpp,v $
 * Revision 1.2  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:27  southa
 * Created Mustl
 *
 * Revision 1.13  2002/12/05 13:20:13  southa
 * Client link handling
 *
 * Revision 1.12  2002/11/28 18:05:36  southa
 * Print link ages
 *
 * Revision 1.11  2002/11/27 13:23:27  southa
 * Server and client data exchange
 *
 * Revision 1.10  2002/11/25 18:02:57  southa
 * Mushware ID work
 *
 * Revision 1.9  2002/11/24 00:29:08  southa
 * Serve web pages to local addresses only
 *
 * Revision 1.8  2002/11/23 14:39:06  southa
 * Store ports in network order
 *
 * Revision 1.7  2002/11/22 15:00:33  southa
 * Network connection handling
 *
 * Revision 1.6  2002/11/21 18:06:18  southa
 * Non-blocking network connection
 *
 * Revision 1.5  2002/11/15 18:58:34  southa
 * Configuration mode
 *
 * Revision 1.4  2002/11/15 11:47:55  southa
 * Web processing and error handling
 *
 * Revision 1.3  2002/11/08 11:54:40  southa
 * Web fixes
 *
 * Revision 1.2  2002/11/04 19:34:47  southa
 * Network link maintenance
 *
 * Revision 1.1  2002/11/03 18:43:09  southa
 * Network fixes
 *
 */

#include "MustlUtils.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlNamespace.h"

bool MustlUtils::m_truncateLog=true;

bool
MustlUtils::FindLinkToStation(MustlLink *& outLink, const MustlAddress& inAddress)
{
    CoreData<MustlLink>::tMapIterator endValue=CoreData<MustlLink>::Instance().End();

    for (CoreData<MustlLink>::tMapIterator p=CoreData<MustlLink>::Instance().Begin();
         p != endValue; ++p)
    {
        COREASSERT(p->second != NULL);
        if (p->second->TCPAddressGet() == inAddress)
        {
            outLink = p->second;
            return true;
        }
    }
    return false;
}

bool
MustlUtils::FindLinkToStation(string& outName, const MustlAddress& inAddress)
{
    CoreData<MustlLink>::tMapIterator endValue=CoreData<MustlLink>::Instance().End();

    for (CoreData<MustlLink>::tMapIterator p=CoreData<MustlLink>::Instance().Begin();
         p != endValue; ++p)
    {
        COREASSERT(p->second != NULL);
        if (p->second->TCPAddressGet() == inAddress)
        {
            outName = p->first;
            return true;
        }
    }
    return false;
}

string
MustlUtils::IPAddressToString(U32 inAddress)
{
    ostringstream ipStream;
    U8 *ipPtr=reinterpret_cast<U8 *>(&inAddress);
    ipStream << static_cast<U32>(ipPtr[0]) << "." << static_cast<U32>(ipPtr[1]) << "." << static_cast<U32>(ipPtr[2]) << "." << static_cast<U32>(ipPtr[3]);
    return ipStream.str();
}

string
MustlUtils::IPAddressToLogString(U32 inAddress)
{
    if (m_truncateLog)
    {
        ostringstream ipStream;
        U8 *ipPtr=reinterpret_cast<U8 *>(&inAddress);
        ipStream << static_cast<U32>(ipPtr[0]) << "." << static_cast<U32>(ipPtr[1]) << ".x.x";
        return ipStream.str();
    }
    else
    {
        return IPAddressToString(inAddress);
    }
}

string
MustlUtils::MsecDurationToString(U32 inMsec)
{
    U32 cumSec = inMsec;
    U32 hourNum=cumSec / 3600000;
    cumSec -= hourNum * 3600000;
    U32 minNum=cumSec / 60000;
    cumSec -= minNum * 60000;
    U32 secNum=cumSec / 1000;
    cumSec -= secNum * 1000;
    U32 deciSecNum=cumSec / 100;

    ostringstream retStream;
    retStream << setfill('0');
    if (hourNum > 0) retStream << hourNum << ":" << setw(2);
    retStream << minNum << ":" << setw(2);
    retStream << secNum << "." << setw(1) << deciSecNum;
    return retStream.str();
}

string
MustlUtils::MakePrintable(const string& inStr)
{
    ostringstream retStream;
    retStream << hex;

    U32 size=inStr.size();
    
    for (U32 i=0; i<size; ++i)
    {
        if (isprint(inStr[i]))
        {
            retStream << inStr[i];
        }
        else
        {
            retStream << "[" << static_cast<U32>(static_cast<U8>(inStr[i])) << "]";
        }
    }
    return retStream.str();
}

string
MustlUtils::MakePrintable(const vector<U8> inBytes)
{
    ostringstream retStream;
    retStream << hex;

    U32 size=inBytes.size();

    for (U32 i=0; i<size; ++i)
    {
        if (isprint(inBytes[i]))
        {
            retStream << inBytes[i];
        }
        else
        {
            retStream << "[" << static_cast<U32>(inBytes[i]) << "]";
        }
    }
    return retStream.str();
}

string
MustlUtils::MakeXMLSafe(const string& inStr)
{
    return MakeWebSafe(inStr);
}

string
MustlUtils::MakeWebSafe(const string& inStr)
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
MustlUtils::RemoveMeta(const string& inStr)
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
