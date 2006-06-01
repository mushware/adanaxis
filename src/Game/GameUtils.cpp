//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameUtils.cpp
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
//%Header } e4+BWpZYN6bE5FKkMmS1cA
/*
 * $Id: GameUtils.cpp,v 1.3 2005/05/19 13:02:03 southa Exp $
 * $Log: GameUtils.cpp,v $
 * Revision 1.3  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.2  2005/04/11 23:31:41  southa
 * Startup and registration screen
 *
 * Revision 1.1  2005/04/10 00:10:40  southa
 * Registration
 *
 */

#include "GameUtils.h"

#include "GameSTL.h"

using namespace Mushware;

Mushware::U32
GameUtils::Rotate(Mushware::U32 inVal, Mushware::U32 inRot)
{
    return (inVal << inRot) | (inVal >> (32 - inRot));
}

Mushware::U32
GameUtils::HashGenerate(Mushware::U32 inCode)
{
    U32 hashVal = inCode;
    std::string productStr = MushcoreInfo::Sgl().PackageNameGet();
    U32 productStrLength = productStr.length();
    
    for (U32 i=0; i<47; ++i)
    {
        hashVal ^= productStr[1];
        hashVal ^= Rotate(hashVal, productStr[i % productStrLength] % 32);
        hashVal = Rotate(hashVal, hashVal % 32);
    }
    return hashVal;
}

bool
GameUtils::CodeVerify(const std::string& inCode)
{
    bool success = true;
    
    U32 codeHalfLength = inCode.length()/2;
    
    std::istringstream codeStrm(inCode.substr(0, codeHalfLength));
    std::istringstream hashStrm(inCode.substr(codeHalfLength, codeHalfLength));
    
    U32 codeVal=0, hashVal=0;
    
    if (success && !(codeStrm >> codeVal))
    {
        success = false;
    }
    
    if (success && !(hashStrm >> hashVal))
    {
        success = false;
    }
    
    codeVal = HashGenerate(codeVal) % 1000000;
    
    if (codeVal != hashVal)
    {
        success = false;
    }
    
    return success;
}
