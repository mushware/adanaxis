/*
 * $Id: CoreParamList.cpp,v 1.2 2002/05/10 16:39:37 southa Exp $
 * $Log: CoreParamList.cpp,v $
 * Revision 1.2  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 */

#include "CoreParamList.h"

void
CoreParamList::PopParam(tVal& outVal)
{
    m_params.front().Get(outVal);
    m_params.pop_front();
}

void
CoreParamList::PopParam(string& outStr)
{
    m_params.front().Get(outStr);
    m_params.pop_front();
}

void
CoreParamList::ostreamPrint(ostream& inOut)
{
    bool first=true;
    while (!Empty())
    {
        string str;
        PopParam(str);
        if (first)
        {
            first=false;
        }
        else
        {
            inOut << ", ";
        }
        inOut << str;
    }
}

        
