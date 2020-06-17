//%includeGuardStart {
#ifndef MUSHGAMECAMERA_H
#define MUSHGAMECAMERA_H
//%includeGuardStart } tzdeCLD2iutbzAqx4mj2vw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameCamera.h
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
//%Header } jBj45HCfsTHN9CMD5Zt+Ww
/*
 * $Id: MushGameCamera.h,v 1.9 2006/10/02 17:25:05 southa Exp $
 * $Log: MushGameCamera.h,v $
 * Revision 1.9  2006/10/02 17:25:05  southa
 * Object lookup and target selection
 *
 * Revision 1.8  2006/07/24 18:46:50  southa
 * Depth sorting
 *
 * Revision 1.7  2006/06/27 11:58:09  southa
 * Warning fixes
 *
 * Revision 1.6  2006/06/01 15:39:20  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/08/01 20:23:24  southa
 * Backdrop and build fixes
 *
 * Revision 1.4  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.2  2005/06/29 09:07:56  southa
 * MushGame camera work
 *
 * Revision 1.1  2005/06/24 10:30:12  southa
 * MushGame camera work
 *
 */

#include "MushGameStandard.h"

#include "MushGamePiece.h"
#include "MushGamePiecePlayer.h"
#include "MushGameRef.h"

#include "API/mushMushGL.h"
#include "API/mushMushMesh.h"

//:xml1base MushGLCamera
//:generate virtual standard ostream xml1
class MushGameCamera : public MushGLCamera
{
public:
    MushGameCamera();
    MushGameCamera(const MushGameCamera& inCamera) : MushGLCamera(inCamera)
    {
        // Deep copy
        if (inCamera.m_pTiedRef == NULL)
        {
            m_pTiedRef = NULL;
        }
        else
        {
            m_pTiedRef = dynamic_cast<MushGameRef *>(inCamera.m_pTiedRef->AutoClone());
            if (m_pTiedRef == NULL)
            {
                throw MushcoreDataFail(std::string("Clone failure: MushGameRef != ")+inCamera.m_pTiedRef->AutoName());
            }
        }
    }
    const MushGameCamera& operator=(const MushGameCamera& inCamera);
    
    virtual ~MushGameCamera();
    
    virtual void FromTiedObjectUpdate(void);
    virtual void TiedRefCopy(MushGameRef *inpRef);
    
private:
    MushGameRef *m_pTiedRef;
    
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
operator<<(std::ostream& ioOut, const MushGameCamera& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } yEL8lWokyDIR1M7RFn0mFw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
