//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerConfig.cpp
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
//%Header } F2FzG63j41XIDNI3vtE/GQ
/*
 * $Id: TesseractTrainerConfig.cpp,v 1.8 2005/07/02 00:42:38 southa Exp $
 * $Log: TesseractTrainerConfig.cpp,v $
 * Revision 1.8  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.7  2005/06/20 14:30:39  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/06/16 17:25:40  southa
 * Client/server work
 *
 * Revision 1.5  2005/05/26 00:46:41  southa
 * Made buildable on win32
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

#include "TesseractTrainerConfig.h"

#include "TesseractTrainerSTL.h"

TesseractTrainerConfig::TesseractTrainerConfig() :
    m_version(1)
{
}

//%outOfLineFunctions {

const char *TesseractTrainerConfig::AutoName(void) const
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
    ioOut << "version=" << m_version << ", ";
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
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "version")
    {
        ioIn >> m_version;
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
    ioOut.TagSet("version");
    ioOut << m_version;
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
//%outOfLineFunctions } Y8/oEQ0xllLAALeUqBtIIQ
