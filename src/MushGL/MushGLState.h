//%includeGuardStart {
#ifndef MUSHGLSTATE_H
#define MUSHGLSTATE_H
//%includeGuardStart } qL9wXSwitdUiB2AgBoaA8A
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLState.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } d/h1MgTijF1xZZlnCvknWQ
/*
 * $Id: MushGLState.h,v 1.1 2005/07/04 11:10:43 southa Exp $
 * $Log: MushGLState.h,v $
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushGLStandard.h"

#include "MushGLVertexBuffer.h"

//:generate standard ostream xml1
class MushGLState : public MushcoreVirtualObject, public MushcoreSingleton<MushGLState>
{
public:
    typedef Mushware::U8 tState;
    enum
    {
        kStateFalse,
        kStateTrue,
        kStateDontCare,
        kStateNone
    };
    
    MushGLState();
    
    
    void ColourArraySet(tState inState) { EffectClientState(m_colourArray, inState, GL_COLOR_ARRAY); }
    void EdgeFlagArraySet(tState inState) { EffectClientState(m_edgeFlagArray, inState, GL_EDGE_FLAG_ARRAY); }
    void IndexArraySet(tState inState) { EffectClientState(m_indexArray, inState, GL_INDEX_ARRAY); }
    void NormalArraySet(tState inState) { EffectClientState(m_normalArray, inState, GL_NORMAL_ARRAY); }
    void TexCoordArraySet(tState inState) { EffectClientState(m_texCoordArray, inState, GL_TEXTURE_COORD_ARRAY); }
    void VertexArraySet(tState inState) { EffectClientState(m_vertexArray, inState, GL_VERTEX_ARRAY); }
        
    void ColourArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer);
    void TexCoordArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer);
    void VertexArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer);
    
    void ArraysDisable(void);
    
    void ResetWriteAll(void) { InvalidateAll(); Reset(); }
    void Reset(void);
    
protected:
    void EffectClientState(tState& ioStateVar, tState inNewState, Mushware::U32 inGLState);
    void InvalidateAll();
    
private:
    tState m_colourArray;
    tState m_edgeFlagArray;
    tState m_indexArray;
    tState m_normalArray;
    tState m_texCoordArray;
    tState m_vertexArray;
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

inline
MushGLState::MushGLState()
{
    InvalidateAll();
}

inline void
MushGLState::InvalidateAll(void)
{
    m_colourArray = kStateNone;
    m_edgeFlagArray = kStateNone;
    m_indexArray = kStateNone;
    m_normalArray = kStateNone;
    m_texCoordArray = kStateNone;
    m_vertexArray = kStateNone;
}

inline void
MushGLState::Reset(void)
{
    ColourArraySet(kStateFalse);
    EdgeFlagArraySet(kStateFalse);
    IndexArraySet(kStateFalse);
    NormalArraySet(kStateFalse);
    TexCoordArraySet(kStateFalse);
    VertexArraySet(kStateFalse);
}

inline void
MushGLState::EffectClientState(Mushware::U8& ioStateVar, Mushware::U8 inNewState, Mushware::U32 inGLState)
{
    if (inNewState != ioStateVar)
    {
        if (inNewState == kStateFalse)
        {
            glDisableClientState(inGLState);
        }
        else if (inNewState == kStateTrue)
        {
            throw MushcoreDataFail("Not willing to set client state to true without address");
        }
    }
    ioStateVar = inNewState;
}

inline void
MushGLState::ColourArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer)
{
    ioBuffer.Bind();
    
    glColorPointer(4, MUSHGL_VALTYPE, 0, ioBuffer.AddrForGLGet());
    
    if (m_colourArray != kStateTrue)
    {
        glEnableClientState(GL_COLOR_ARRAY);
    }
    m_colourArray = kStateTrue;
}

inline void
MushGLState::TexCoordArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer)
{
    throw MushcoreLogicFail("TexCoordArraySetTrue not implemented");
}

inline void
MushGLState::VertexArraySetTrue(MushGLVertexBuffer<Mushware::t4GLVal>& ioBuffer)
{
    ioBuffer.Bind();
    
    glVertexPointer(4, MUSHGL_VALTYPE, 0, ioBuffer.AddrForGLGet());
    
    if (m_vertexArray != kStateTrue)
    {
        glEnableClientState(GL_VERTEX_ARRAY);
    }
    m_vertexArray = kStateTrue;
}

inline void
MushGLState::ArraysDisable(void)
{
    ColourArraySet(kStateFalse);
    EdgeFlagArraySet(kStateFalse);
    IndexArraySet(kStateFalse);
    NormalArraySet(kStateFalse);
    TexCoordArraySet(kStateFalse);
    VertexArraySet(kStateFalse);
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLState& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } fDBPEHo0FNe/dqIH6odASw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
