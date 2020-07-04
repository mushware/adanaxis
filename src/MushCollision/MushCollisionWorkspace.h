//%includeGuardStart {
#ifndef MUSHCOLLISIONWORKSPACE_H
#define MUSHCOLLISIONWORKSPACE_H
//%includeGuardStart } PcPOuVXCJDuUEvDz0vLtAQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionWorkspace.h
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
//%Header } Y5tGCQvPzMnNRG4jMgSWSA
/*
 * $Id: MushCollisionWorkspace.h,v 1.4 2006/06/01 15:39:16 southa Exp $
 * $Log: MushCollisionWorkspace.h,v $
 * Revision 1.4  2006/06/01 15:39:16  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/30 19:06:14  southa
 * Collision checking
 *
 * Revision 1.2  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.1  2005/07/27 18:09:59  southa
 * Collision checking
 *
 */

#include "MushCollisionStandard.h"

//:generate virtual standard ostream xml1
class MushCollisionWorkspace : public MushcoreVirtualObject
{
public:
    typedef std::vector<Mushware::t4Val> tChunkCentroids;
    MushCollisionWorkspace();

    void Touch(void); // Called by constructor
    void ResetIfNeeded(Mushware::tMsec inFrameMsec);
    
private:
    Mushware::tMsec m_frameMsec; //:readwrite
    Mushware::t4Val m_centroid; //:readwrite :wref
    tChunkCentroids m_chunkCentroids; //:readwrite :wref
    
    bool m_centroidValid; //:readwrite
    bool m_chunkCentroidsValid; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::tMsec& FrameMsec(void) const { return m_frameMsec; }
    void FrameMsecSet(const Mushware::tMsec& inValue) { m_frameMsec=inValue; }
    const Mushware::t4Val& Centroid(void) const { return m_centroid; }
    void CentroidSet(const Mushware::t4Val& inValue) { m_centroid=inValue; }
    // Writable reference for m_centroid
    Mushware::t4Val& CentroidWRef(void) { return m_centroid; }
    const tChunkCentroids& ChunkCentroids(void) const { return m_chunkCentroids; }
    void ChunkCentroidsSet(const tChunkCentroids& inValue) { m_chunkCentroids=inValue; }
    // Writable reference for m_chunkCentroids
    tChunkCentroids& ChunkCentroidsWRef(void) { return m_chunkCentroids; }
    const bool& CentroidValid(void) const { return m_centroidValid; }
    void CentroidValidSet(const bool& inValue) { m_centroidValid=inValue; }
    const bool& ChunkCentroidsValid(void) const { return m_chunkCentroidsValid; }
    void ChunkCentroidsValidSet(const bool& inValue) { m_chunkCentroidsValid=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } OBFgasRLxn9Yl9EYFJenKg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushCollisionWorkspace& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } /+uw7H0WmUwZEJh3oyHk/g
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
