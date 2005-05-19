//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerConfig.cpp
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
//%Header } M3UkBs5T8BrIGUpcmTAdqg
/*
 * $Id: TesseractTrainerConfig.cpp,v 1.2 2005/04/19 23:25:43 southa Exp $
 * $Log: TesseractTrainerConfig.cpp,v $
 * Revision 1.2  2005/04/19 23:25:43  southa
 * Mode switching and recognition
 *
 * Revision 1.1  2005/04/19 19:23:14  southa
 * Save and load config
 *
 */

#include "TesseractTrainerConfig.h"

//%outOfLineFunctions {

const char *TesseractTrainerConfig::AutoNameGet(void) const
{
    return "TesseractTrainerConfig";
}

MushcoreVirtualObject *TesseractTrainerConfig::AutoClone(void) const
{
    return new TesseractTrainerConfig(*this);
}

MushcoreVirtualObject *TesseractTrainerConfig::AutoCreate(void) const
{
    return new TesseractTrainerConfig;
}

MushcoreVirtualObject *TesseractTrainerConfig::AutoVirtualFactory(void)
{
    return new TesseractTrainerConfig;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("TesseractTrainerConfig", TesseractTrainerConfig::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
TesseractTrainerConfig::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "rotationChangeMsec=" << m_rotationChangeMsec << ", ";
    ioOut << "realignMsec=" << m_realignMsec << ", ";
    ioOut << "lineWidth=" << m_lineWidth << ", ";
    ioOut << "pointSize=" << m_pointSize << ", ";
    ioOut << "objectDistance=" << m_objectDistance << ", ";
    ioOut << "renderFaces=" << m_renderFaces << ", ";
    ioOut << "renderFaceOutlines=" << m_renderFaceOutlines << ", ";
    ioOut << "renderFaceTextures=" << m_renderFaceTextures << ", ";
    ioOut << "renderFacePoints=" << m_renderFacePoints << ", ";
    ioOut << "renderRotationPlanes=" << m_renderRotationPlanes << ", ";
    ioOut << "renderBasicPlanes=" << m_renderBasicPlanes << ", ";
    ioOut << "renderStereo=" << m_renderStereo << ", ";
    ioOut << "stereoEyeSeparation=" << m_stereoEyeSeparation << ", ";
    ioOut << "stereoImageSeparation=" << m_stereoImageSeparation << ", ";
    ioOut << "displayMode=" << m_displayMode << ", ";
    ioOut << "playMusic=" << m_playMusic;
    ioOut << "]";
}
bool
TesseractTrainerConfig::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "rotationChangeMsec")
    {
        ioIn >> m_rotationChangeMsec;
    }
    else if (inTagStr == "realignMsec")
    {
        ioIn >> m_realignMsec;
    }
    else if (inTagStr == "lineWidth")
    {
        ioIn >> m_lineWidth;
    }
    else if (inTagStr == "pointSize")
    {
        ioIn >> m_pointSize;
    }
    else if (inTagStr == "objectDistance")
    {
        ioIn >> m_objectDistance;
    }
    else if (inTagStr == "renderFaces")
    {
        ioIn >> m_renderFaces;
    }
    else if (inTagStr == "renderFaceOutlines")
    {
        ioIn >> m_renderFaceOutlines;
    }
    else if (inTagStr == "renderFaceTextures")
    {
        ioIn >> m_renderFaceTextures;
    }
    else if (inTagStr == "renderFacePoints")
    {
        ioIn >> m_renderFacePoints;
    }
    else if (inTagStr == "renderRotationPlanes")
    {
        ioIn >> m_renderRotationPlanes;
    }
    else if (inTagStr == "renderBasicPlanes")
    {
        ioIn >> m_renderBasicPlanes;
    }
    else if (inTagStr == "renderStereo")
    {
        ioIn >> m_renderStereo;
    }
    else if (inTagStr == "stereoEyeSeparation")
    {
        ioIn >> m_stereoEyeSeparation;
    }
    else if (inTagStr == "stereoImageSeparation")
    {
        ioIn >> m_stereoImageSeparation;
    }
    else if (inTagStr == "displayMode")
    {
        ioIn >> m_displayMode;
    }
    else if (inTagStr == "playMusic")
    {
        ioIn >> m_playMusic;
    }
    else
    {
        return false;
    }
    return true;
}
void
TesseractTrainerConfig::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("rotationChangeMsec");
    ioOut << m_rotationChangeMsec;
    ioOut.TagSet("realignMsec");
    ioOut << m_realignMsec;
    ioOut.TagSet("lineWidth");
    ioOut << m_lineWidth;
    ioOut.TagSet("pointSize");
    ioOut << m_pointSize;
    ioOut.TagSet("objectDistance");
    ioOut << m_objectDistance;
    ioOut.TagSet("renderFaces");
    ioOut << m_renderFaces;
    ioOut.TagSet("renderFaceOutlines");
    ioOut << m_renderFaceOutlines;
    ioOut.TagSet("renderFaceTextures");
    ioOut << m_renderFaceTextures;
    ioOut.TagSet("renderFacePoints");
    ioOut << m_renderFacePoints;
    ioOut.TagSet("renderRotationPlanes");
    ioOut << m_renderRotationPlanes;
    ioOut.TagSet("renderBasicPlanes");
    ioOut << m_renderBasicPlanes;
    ioOut.TagSet("renderStereo");
    ioOut << m_renderStereo;
    ioOut.TagSet("stereoEyeSeparation");
    ioOut << m_stereoEyeSeparation;
    ioOut.TagSet("stereoImageSeparation");
    ioOut << m_stereoImageSeparation;
    ioOut.TagSet("displayMode");
    ioOut << m_displayMode;
    ioOut.TagSet("playMusic");
    ioOut << m_playMusic;
}
//%outOfLineFunctions } yQdHWm9BP58yfj5artL3kA
