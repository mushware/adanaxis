/*
 * $Id$
 * $Log$
 */

#include "CoreParamList.hp"

void
CoreParamList::PopParam(Val& outVal)
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

        
