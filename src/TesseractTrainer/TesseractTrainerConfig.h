//%includeGuardStart {
#ifndef TESSERACTTRAINERCONFIG_H
#define TESSERACTTRAINERCONFIG_H
//%includeGuardStart } JlYeS3QzVCNp4/ccCPu06g
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerConfig.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } HM/+Le0G4xzcG+RVw/JE4w
/*
 * $Id: TesseractTrainerConfig.h,v 1.8 2006/06/01 15:39:59 southa Exp $
 * $Log: TesseractTrainerConfig.h,v $
 * Revision 1.8  2006/06/01 15:39:59  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.6  2005/06/20 14:30:39  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/06/08 20:59:52  southa
 * X11 release
 *
 * Revision 1.4  2005/05/20 10:26:29  southa
 * Release work
 *
 * Revision 1.3  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.2  2005/04/19 23:25:43  southa
 * Mode switching and recognition
 *
 * Revision 1.1  2005/04/19 19:23:14  southa
 * Save and load config
 *
 */

#include "TesseractTrainerStandard.h"

//:generate standard ostream xml1
class TesseractTrainerConfig : public MushcoreVirtualObject
{
public:
    TesseractTrainerConfig();
    
private:
    Mushware::U32 m_version;
    Mushware::tVal m_rotationChangeMsec; //:readwrite
    Mushware::tVal m_realignMsec; //:readwrite
    Mushware::tVal m_lineWidth; //:readwrite
    Mushware::tVal m_pointSize; //:readwrite
    Mushware::tVal m_objectDistance; //:readwrite
    
    Mushware::U32 m_renderFaces; //:readwrite :wref
    Mushware::U32 m_renderFaceOutlines; //:readwrite :wref
    bool m_renderFaceTextures; //:readwrite :toggle
    Mushware::U32 m_renderFacePoints; //:readwrite :wref
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
    const Mushware::U32& RenderFaceOutlines(void) const { return m_renderFaceOutlines; }
    void RenderFaceOutlinesSet(const Mushware::U32& inValue) { m_renderFaceOutlines=inValue; }
    // Writable reference for m_renderFaceOutlines
    Mushware::U32& RenderFaceOutlinesWRef(void) { return m_renderFaceOutlines; }
    const bool& RenderFaceTextures(void) const { return m_renderFaceTextures; }
    void RenderFaceTexturesSet(const bool& inValue) { m_renderFaceTextures=inValue; }
    void RenderFaceTexturesToggle(void) { m_renderFaceTextures=!(m_renderFaceTextures); }
    const Mushware::U32& RenderFacePoints(void) const { return m_renderFacePoints; }
    void RenderFacePointsSet(const Mushware::U32& inValue) { m_renderFacePoints=inValue; }
    // Writable reference for m_renderFacePoints
    Mushware::U32& RenderFacePointsWRef(void) { return m_renderFacePoints; }
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
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } JU5PE3O5oWIkm4dLmn+6lg
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
