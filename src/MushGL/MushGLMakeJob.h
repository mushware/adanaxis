//%includeGuardStart {
#ifndef MUSHGLMAKEJOB_H
#define MUSHGLMAKEJOB_H
//%includeGuardStart } crflqN9HxBc5EDJ0n35ugA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLMakeJob.h
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
//%Header } pdHhCBpAbnBkUyf3LvGAoQ

#include "MushGLStandard.h"

#include "API/mushMedia.h"

class MushGLPixelSource;
class MushGLTexture;

//:generate virtual standard ostream xml1
class MushGLMakeJob : public MediaJob {
public:
    MushGLMakeJob();
    MushGLMakeJob(std::string& name, MushGLPixelSource *pPixelSource, MushGLTexture *pTexture);
    virtual ~MushGLMakeJob();

    virtual void PrerequisitesCreate();
    virtual void Run();
    virtual void MainThreadPostRun();

private:
    MushGLPixelSource *m_pPixelSource; // This object own this
    MushGLTexture *m_pTexture;

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
operator<<(std::ostream& ioOut, const MushGLMakeJob& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } pMMKT4yLCbdquqEXXSdyrg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
