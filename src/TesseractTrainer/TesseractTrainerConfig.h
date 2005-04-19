//%includeGuardStart {
#ifndef TESSERACTTRAINERCONFIG_H
#define TESSERACTTRAINERCONFIG_H
//%includeGuardStart } JlYeS3QzVCNp4/ccCPu06g
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerConfig.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } F/CgXVUSoDn7bRpiFwrEYQ
/*
 * $Id: TesseractTrainerConfig.h,v 1.1 2005/04/19 19:23:14 southa Exp $
 * $Log: TesseractTrainerConfig.h,v $
 * Revision 1.1  2005/04/19 19:23:14  southa
 * Save and load config
 *
 */

#include "TesseractTrainerStandard.h"

//:generate standard ostream xml1
class TesseractTrainerConfig : public MushcoreVirtualObject
{
public:
    
private:
    Mushware::tVal m_rotationChangeMsec; //:readwrite
    Mushware::tVal m_realignMsec; //:readwrite
    Mushware::tVal m_lineWidth; //:readwrite
    Mushware::tVal m_pointSize; //:readwrite
    Mushware::tVal m_objectDistance; //:readwrite
    
    Mushware::U32 m_renderFaces; //:readwrite :wref
    bool m_renderFaceOutlines; //:readwrite :toggle
    bool m_renderFaceTextures; //:readwrite :toggle
    bool m_renderFacePoints; //:readwrite :toggle
    bool m_renderRotationPlanes; //:readwrite :toggle
    bool m_renderBasicPlanes; //:readwrite :toggle
    bool m_renderStereo; //:readwrite :toggle
    Mushware::tVal m_stereoEyeSeparation; //:readwrite
    Mushware::tVal m_stereoImageSeparation; //:readwrite
    Mushware::U32 m_displayMode; //:readwrite
    bool m_playMusic; //:readwrite :toggle
    
//%classPrototypes {
public:
    const Mushware::tVal& RotationChangeMsec(void) const { return m_rotationChangeMsec; }
    void RotationChangeMsecSet(const Mushware::tVal& inValue) { m_rotationChangeMsec=inValue; }
    const Mushware::tVal& RealignMsec(void) const { return m_realignMsec; }
    void RealignMsecSet(const Mushware::tVal& inValue) { m_realignMsec=inValue; }
    const Mushware::tVal& LineWidth(void) const { return m_lineWidth; }
    void LineWidthSet(const Mushware::tVal& inValue) { m_lineWidth=inValue; }
    const Mushware::tVal& PointSize(void) const { return m_pointSize; }
    void PointSizeSet(const Mushware::tVal& inValue) { m_pointSize=inValue; }
    const Mushware::tVal& ObjectDistance(void) const { return m_objectDistance; }
    void ObjectDistanceSet(const Mushware::tVal& inValue) { m_objectDistance=inValue; }
    const Mushware::U32& RenderFaces(void) const { return m_renderFaces; }
    void RenderFacesSet(const Mushware::U32& inValue) { m_renderFaces=inValue; }
    // Writable reference for m_renderFaces
    Mushware::U32& RenderFacesWRef(void) { return m_renderFaces; }
    const bool& RenderFaceOutlines(void) const { return m_renderFaceOutlines; }
    void RenderFaceOutlinesSet(const bool& inValue) { m_renderFaceOutlines=inValue; }
    void RenderFaceOutlinesToggle(void) { m_renderFaceOutlines=!(m_renderFaceOutlines); }
    const bool& RenderFaceTextures(void) const { return m_renderFaceTextures; }
    void RenderFaceTexturesSet(const bool& inValue) { m_renderFaceTextures=inValue; }
    void RenderFaceTexturesToggle(void) { m_renderFaceTextures=!(m_renderFaceTextures); }
    const bool& RenderFacePoints(void) const { return m_renderFacePoints; }
    void RenderFacePointsSet(const bool& inValue) { m_renderFacePoints=inValue; }
    void RenderFacePointsToggle(void) { m_renderFacePoints=!(m_renderFacePoints); }
    const bool& RenderRotationPlanes(void) const { return m_renderRotationPlanes; }
    void RenderRotationPlanesSet(const bool& inValue) { m_renderRotationPlanes=inValue; }
    void RenderRotationPlanesToggle(void) { m_renderRotationPlanes=!(m_renderRotationPlanes); }
    const bool& RenderBasicPlanes(void) const { return m_renderBasicPlanes; }
    void RenderBasicPlanesSet(const bool& inValue) { m_renderBasicPlanes=inValue; }
    void RenderBasicPlanesToggle(void) { m_renderBasicPlanes=!(m_renderBasicPlanes); }
    const bool& RenderStereo(void) const { return m_renderStereo; }
    void RenderStereoSet(const bool& inValue) { m_renderStereo=inValue; }
    void RenderStereoToggle(void) { m_renderStereo=!(m_renderStereo); }
    const Mushware::tVal& StereoEyeSeparation(void) const { return m_stereoEyeSeparation; }
    void StereoEyeSeparationSet(const Mushware::tVal& inValue) { m_stereoEyeSeparation=inValue; }
    const Mushware::tVal& StereoImageSeparation(void) const { return m_stereoImageSeparation; }
    void StereoImageSeparationSet(const Mushware::tVal& inValue) { m_stereoImageSeparation=inValue; }
    const Mushware::U32& DisplayMode(void) const { return m_displayMode; }
    void DisplayModeSet(const Mushware::U32& inValue) { m_displayMode=inValue; }
    const bool& PlayMusic(void) const { return m_playMusic; }
    void PlayMusicSet(const bool& inValue) { m_playMusic=inValue; }
    void PlayMusicToggle(void) { m_playMusic=!(m_playMusic); }
    const char *AutoNameGet(void) const;
    MushcoreVirtualObject *AutoClone(void) const;
    MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } YgDPPEGtTgk5BwsRt0VzKw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const TesseractTrainerConfig& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } LZ7YpOR4H4iOI/6OimT/Zw

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
