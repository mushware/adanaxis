/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: CoreParamList.cpp,v 1.4 2002/05/28 16:37:36 southa Exp $
 * $Log: CoreParamList.cpp,v $
 * Revision 1.4  2002/05/28 16:37:36  southa
 * Texture references and decomposer
 *
 * Revision 1.3  2002/05/24 16:23:09  southa
 * Config and typenames
 *
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
    if (!m_params.empty())
    {
        m_params.front().Get(outVal);
        m_params.pop_front();
    }
}

void
CoreParamList::PopParam(string& outStr)
{
    if (!m_params.empty())
    {
        m_params.front().Get(outStr);
        m_params.pop_front();
    }
}

void
CoreParamList::PopParam(U32 &outU32)
{
    if (!m_params.empty())
    {
        tVal val;
        m_params.front().Get(val);
        m_params.pop_front();
        outU32=static_cast<U32>(val);
    }
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

        
