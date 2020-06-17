//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameUtils.cpp
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
//%Header } 8YTe98JUTQDXR3KkHdpxvw
/*
 * $Id: GameUtils.cpp,v 1.4 2006/06/01 15:39:00 southa Exp $
 * $Log: GameUtils.cpp,v $
 * Revision 1.4  2006/06/01 15:39:00  southa
 * DrawArray verification and fixes
 *
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
