//%includeGuardStart {
#ifndef ADANAXISPIECEWORLD_H
#define ADANAXISPIECEWORLD_H
//%includeGuardStart } yMM+emyFXLFbQRCK187Htg
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceWorld.h
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
//%Header } 4DTCHgfQrjIS8EKmgrF4YA
/*
 * $Id: AdanaxisPieceWorld.h,v 1.4 2007/04/18 09:22:02 southa Exp $
 * $Log: AdanaxisPieceWorld.h,v $
 * Revision 1.4  2007/04/18 09:22:02  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/10/30 17:03:51  southa
 * Remnants creation
 *
 * Revision 1.2  2006/08/01 17:21:26  southa
 * River demo
 *
 * Revision 1.1  2006/07/19 10:22:15  southa
 * World objects
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisPiece.h"

#include "API/mushMushGL.h"
#include "API/mushMushMesh.h"
#include "API/mushMushRender.h"

//:xml1base MushGamePiece
//:generate virtual standard ostream xml1
class AdanaxisPieceWorld : public MushGamePiece
{
public:
    explicit AdanaxisPieceWorld(const std::string& inID = "");
    
    virtual void Render(MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera);
private:
        
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisPieceWorld& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } +6D5ssvr6WCcjMqQ4Y2w3g
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
