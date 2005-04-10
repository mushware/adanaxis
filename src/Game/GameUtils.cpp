//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameUtils.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } KH3rkSKlI7syV0i8D7gvNg
/*
 * $Id$
 * $Log$
 */

#include "GameUtils.h"

#include "GameSTL.h"

using namespace Mushware;

Mushware::U32
GameUtils::Rotate(Mushware::U32 inVal, Mushware::U32 inRot)
{
    return (inVal << inRot) | (inVal >> (32 - inRot));
}

bool
GameUtils::CodeVerify(const std::string& inCode)
{
    bool success = true;
    
    U32 codeHalfLength = inCode.length()/2;
    
    std::string productStr = MushcoreInfo::Sgl().PackageNameGet();
    U32 productStrLength = productStr.length();
    
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
    
    for (U32 i=0; i<47; ++i)
    {
        codeVal ^= productStr[1];
        codeVal ^= Rotate(codeVal, productStr[i % productStrLength] % 32);
        codeVal = Rotate(codeVal, codeVal % 32);
    }
    
    codeVal = codeVal % 1000000;
    
    std::cerr << codeVal << std::endl;

    if (codeVal != hashVal)
    {
        success = false;
    }
    
    return success;
}
