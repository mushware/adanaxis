/*
 * $Id: MediaNetUtils.cpp,v 1.4 2002/11/15 11:47:55 southa Exp $
 * $Log: MediaNetUtils.cpp,v $
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

#include "MediaNetUtils.h"

string
MediaNetUtils::IPAddressToString(U32 inAddress)
{
    ostringstream ipStream;
    U8 *ipPtr=reinterpret_cast<U8 *>(&inAddress);
    ipStream << static_cast<U32>(ipPtr[0]) << "." << static_cast<U32>(ipPtr[1]) << "." << static_cast<U32>(ipPtr[2]) << "." << static_cast<U32>(ipPtr[3]);
    return ipStream.str();
}

string
MediaNetUtils::MakePrintable(const string& inStr)
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
            retStream << "[" << static_cast<U32>(inStr[i]) << "]";
        }
    }
    return retStream.str();
}

string
MediaNetUtils::MakePrintable(const vector<U8> inBytes)
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
MediaNetUtils::MakeWebSafe(const string& inStr)
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
MediaNetUtils::RemoveMeta(const string& inStr)
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