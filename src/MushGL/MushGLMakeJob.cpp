//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLMakeJob.cpp
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
//%Header } l5DuuBK3m6VwRVhAJD4XZw

#include "MushGLMakeJob.h"

#include "MushGLCacheControl.h"
#include "MushGLPixelSource.h"
#include "MushGLTexture.h"

MushGLMakeJob::MushGLMakeJob() :
    m_pTexture(NULL)
{
    MediaJob::MediaJob();
}


MushGLMakeJob::MushGLMakeJob(std::string& name, MushGLPixelSource *pPixelSource, MushGLTexture *pTexture) :
    MediaJob::MediaJob(name, "GL"),
    m_pPixelSource(dynamic_cast<MushGLPixelSource *>(pPixelSource->AutoClone())),
    m_pTexture(pTexture)
{
}


MushGLMakeJob::~MushGLMakeJob()
{
    delete m_pPixelSource;
}


void
MushGLMakeJob::PrerequisitesCreate()
{
    if (m_pTexture == NULL) {
        throw MushcoreRequestFail("MushGLMakeJob has no texture to make");
    }
    if (m_pPixelSource == NULL) {
        throw MushcoreRequestFail("MushGLMakeJob has no pixel source");
    }
    std::vector<MediaJobId> jobIds = m_pPixelSource->PrerequisitesCreate(*m_pTexture);
    
    JobIdToWaitForAdd(jobIds);
}


void MushGLMakeJob::Run()
{
    m_pPixelSource->DataCreate();

    m_pPixelSource->ToTextureCreate(*m_pTexture, &m_killSwitch);

    // Built this texture the hard way, so save to cache
    if (m_pTexture->Cacheable() && MushGLCacheControl::Sgl().PermitCache())
    {
        if (m_pPixelSource->ReductionFactor() < 1.5) {
            // Final copy
            m_pTexture->ToCacheSave(*m_pPixelSource);
        } else {
#ifdef MUSHCORE_DEBUG
            std::string cacheFilename = m_pTexture->CacheFilename();
            std::ostringstream nameStream;
            nameStream << m_pTexture->Name() << "-reduce" << m_pPixelSource->ReductionFactor();
            m_pTexture->CacheFilenameSet(MushGLCacheControl::Sgl().TextureCacheFilenameMake(
                nameStream.str(),
                m_pTexture->UniqueIdentifier(),
                Mushware::t2U32(m_pTexture->Size().X(),
                    m_pTexture->Size().Y()))
            );
            
            m_pTexture->ToCacheSave(*m_pPixelSource);

            m_pTexture->CacheFilenameSet(cacheFilename);
#endif
        }
    }

    JobStateSet(kJobStatePostRun);
}


void MushGLMakeJob::MainThreadPostRun()
{
    m_pPixelSource->ToTextureBind(*m_pTexture);
    m_pPixelSource->DataRelease();

    m_pTexture->ReadySet(true);

    Mushware::tVal reductionFactor = m_pPixelSource->ReductionFactor();
    m_pPixelSource->ReductionFactorSet(reductionFactor / 2);

    if (reductionFactor < 1.5) {
        m_pTexture->FinishedSet(true);
    }

    if (m_pTexture->Finished()) {
        JobStateSet(kJobStateDone);
    } else {
        JobStateSet(kJobStateQueueAgain);
    }
}

//%outOfLineFunctions {

const char *MushGLMakeJob::AutoName(void) const
{
    return "MushGLMakeJob";
}

MushcoreVirtualObject *MushGLMakeJob::AutoClone(void) const
{
    return new MushGLMakeJob(*this);
}

MushcoreVirtualObject *MushGLMakeJob::AutoCreate(void) const
{
    return new MushGLMakeJob;
}

MushcoreVirtualObject *MushGLMakeJob::AutoVirtualFactory(void)
{
    return new MushGLMakeJob;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLMakeJob", MushGLMakeJob::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLMakeJob::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    if (m_pPixelSource == NULL)
    {
        ioOut << "pPixelSource=NULL"  << ", ";
    }
    else
    {
        ioOut << "pPixelSource=" << *m_pPixelSource << ", ";
    }
    if (m_pTexture == NULL)
    {
        ioOut << "pTexture=NULL" ;
    }
    else
    {
        ioOut << "pTexture=" << *m_pTexture;
    }
    ioOut << "]";
}
bool
MushGLMakeJob::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "pPixelSource")
    {
        ioIn >> m_pPixelSource;
    }
    else if (inTagStr == "pTexture")
    {
        ioIn >> m_pTexture;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLMakeJob::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("pPixelSource");
    ioOut << m_pPixelSource;
    ioOut.TagSet("pTexture");
    ioOut << m_pTexture;
}
//%outOfLineFunctions } bf5CeSCEgqagfap8G92quQ
