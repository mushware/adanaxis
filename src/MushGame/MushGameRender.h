//%includeGuardStart {
#ifndef MUSHGAMERENDER_H
#define MUSHGAMERENDER_H
//%includeGuardStart } XiswxIPXAt8y2emYXbfSKw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRender.h
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
//%Header } 7TSItGPho4DqlDsBhWy5qQ
/*
 * $Id: MushGameRender.h,v 1.6 2007/02/08 17:55:15 southa Exp $
 * $Log: MushGameRender.h,v $
 * Revision 1.6  2007/02/08 17:55:15  southa
 * Common routines in space generation
 *
 * Revision 1.5  2006/07/20 12:22:22  southa
 * Precache display
 *
 * Revision 1.4  2006/06/01 15:39:26  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/08/01 20:23:18  southa
 * Backdrop and build fixes
 *
 * Revision 1.2  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 */

#include "MushGameStandard.h"

class MushGameCamera;
class MushGameLogic;

//:generate standard ostream xml1
class MushGameRender : public MushcoreVirtualObject
{
public:
    virtual ~MushGameRender() {}
    virtual void GroupingNameSet(const std::string& inName) { m_groupingName = inName; }

    virtual void PrecacheRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera);
    virtual void FrameRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera);
    
private:
    std::string m_groupingName; //:read

//%classPrototypes {
public:
    const std::string& GroupingName(void) const { return m_groupingName; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } LwveyIxAwfx75093rFgjKg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameRender& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Sfh3sa00ACUii0SCfVWg5g
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
