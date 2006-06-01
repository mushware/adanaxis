//%includeGuardStart {
#ifndef TESSERACTTRAINERHYPERCUBE_H
#define TESSERACTTRAINERHYPERCUBE_H
//%includeGuardStart } N2+eFZbi2SVio7k4AGYf3Q
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerHypercube.h
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
//%Header } wdf3o76m0am0zHR6XXY/NA
/*
 * $Id: TesseractTrainerHypercube.h,v 1.5 2005/05/19 13:02:22 southa Exp $
 * $Log: TesseractTrainerHypercube.h,v $
 * Revision 1.5  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.4  2005/03/13 00:34:48  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.3  2005/02/26 17:53:46  southa
 * Plane sets and pairs
 *
 * Revision 1.2  2005/02/13 22:44:08  southa
 * Tesseract stuff
 *
 * Revision 1.1  2005/02/03 15:46:58  southa
 * Quaternion work
 *
 */

#include "TesseractTrainerStandard.h"

#include "mushMushGL.h"
#include "mushMushMesh.h"

//:generate
class TesseractTrainerHypercube
{
public:
    typedef Mushware::t4Val tVertex;
    typedef Mushware::t2Val tTexCoord;
    typedef MushMeshGroup tFacetGroup;
    
    TesseractTrainerHypercube() {}
    void Create(Mushware::tVal frame, const std::vector<Mushware::t4GLVal>& inColours);
    void Render(Mushware::tVal frame);
    void OrientationSet(const Mushware::tQValPair& inOrient) { m_orientation = inOrient; }
    
private:
    std::vector<tVertex> m_vertices;
    std::vector<Mushware::t4GLVal> m_colours;
    std::vector<tTexCoord> m_texCoords;
    MushcoreDataRef<GLTexture> m_textureRef;
    tFacetGroup m_facetGroup;
    Mushware::tQValPair m_orientation;
    Mushware::U32 m_renderFaces; //:readwrite
    bool m_renderFaceOutlines; //:readwrite
    bool m_renderFaceTextures; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& RenderFaces(void) const { return m_renderFaces; }
    void RenderFacesSet(const Mushware::U32& inValue) { m_renderFaces=inValue; }
    const bool& RenderFaceOutlines(void) const { return m_renderFaceOutlines; }
    void RenderFaceOutlinesSet(const bool& inValue) { m_renderFaceOutlines=inValue; }
    const bool& RenderFaceTextures(void) const { return m_renderFaceTextures; }
    void RenderFaceTexturesSet(const bool& inValue) { m_renderFaceTextures=inValue; }
//%classPrototypes } F2TMclDxJ+51bLL6iBr8iQ
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
