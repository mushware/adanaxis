//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisVolatileData.cpp
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
//%Header } ScAWeuEJNjAM8OwqQx9t7A
/*
 * $Id: AdanaxisVolatileData.cpp,v 1.21 2007/06/14 18:55:11 southa Exp $
 * $Log: AdanaxisVolatileData.cpp,v $
 * Revision 1.21  2007/06/14 18:55:11  southa
 * Level and display tweaks
 *
 * Revision 1.20  2007/05/09 19:24:44  southa
 * Level 14
 *
 * Revision 1.19  2007/04/18 20:08:40  southa
 * Tweaks and fixes
 *
 * Revision 1.18  2007/04/18 09:22:05  southa
 * Header and level fixes
 *
 * Revision 1.17  2007/04/16 08:41:09  southa
 * Level and header mods
 *
 * Revision 1.16  2007/03/19 16:01:36  southa
 * Damage indicators
 *
 * Revision 1.15  2007/03/16 19:50:44  southa
 * Damage indicators
 *
 * Revision 1.14  2007/03/13 18:21:37  southa
 * Scanner jamming
 *
 * Revision 1.13  2007/03/09 11:29:13  southa
 * Game end actions
 *
 * Revision 1.12  2007/03/07 16:59:44  southa
 * Khazi spawning and level ends
 *
 * Revision 1.11  2006/11/12 20:09:55  southa
 * Missile guidance
 *
 * Revision 1.10  2006/08/01 17:21:30  southa
 * River demo
 *
 * Revision 1.9  2006/07/28 16:52:19  southa
 * Options work
 *
 * Revision 1.8  2006/07/26 16:37:21  southa
 * Options menu
 *
 * Revision 1.7  2006/07/19 10:22:15  southa
 * World objects
 *
 * Revision 1.6  2006/07/04 16:55:26  southa
 * Ruby key handling
 *
 * Revision 1.5  2006/07/02 21:08:54  southa
 * Ruby menu work
 *
 */

#include "AdanaxisVolatileData.h"

AdanaxisVolatileData::AdanaxisVolatileData() :
    m_rubySpace(Mushware::kRubyQnil),
    m_scannerOn(false),
    m_khaziCount(0),
    m_khaziRedCount(0),
    m_khaziBlueCount(0),
    m_jammerCount(0),
    m_playerCount(0),
    m_damageIcons(6, 0) // size is 6
{
}

//%outOfLineFunctions {

const char *AdanaxisVolatileData::AutoName(void) const
{
    return "AdanaxisVolatileData";
}

MushcoreVirtualObject *AdanaxisVolatileData::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'AdanaxisVolatileData'");;
}

MushcoreVirtualObject *AdanaxisVolatileData::AutoCreate(void) const
{
    return new AdanaxisVolatileData;
}

MushcoreVirtualObject *AdanaxisVolatileData::AutoVirtualFactory(void)
{
    return new AdanaxisVolatileData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisVolatileData", AdanaxisVolatileData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisVolatileData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameVolatileData::AutoPrint(ioOut);
    ioOut << "decoList=" << m_decoList << ", ";
    ioOut << "worldList=" << m_worldList << ", ";
    ioOut << "aRenderMesh=" << m_aRenderMesh << ", ";
    ioOut << "rubySpace=" << m_rubySpace << ", ";
    ioOut << "brightness=" << m_brightness << ", ";
    ioOut << "showFps=" << m_showFps << ", ";
    ioOut << "scannerOn=" << m_scannerOn << ", ";
    ioOut << "playerTargetID=" << m_playerTargetID << ", ";
    ioOut << "khaziCount=" << m_khaziCount << ", ";
    ioOut << "khaziRedCount=" << m_khaziRedCount << ", ";
    ioOut << "khaziBlueCount=" << m_khaziBlueCount << ", ";
    ioOut << "khaziRedTotal=" << m_khaziRedTotal << ", ";
    ioOut << "khaziBlueTotal=" << m_khaziBlueTotal << ", ";
    ioOut << "jammerCount=" << m_jammerCount << ", ";
    ioOut << "playerCount=" << m_playerCount << ", ";
    ioOut << "damageIcons=" << m_damageIcons;
    ioOut << "]";
}
bool
AdanaxisVolatileData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "decoList")
    {
        ioIn >> m_decoList;
    }
    else if (inTagStr == "worldList")
    {
        ioIn >> m_worldList;
    }
    else if (inTagStr == "aRenderMesh")
    {
        ioIn >> m_aRenderMesh;
    }
    else if (inTagStr == "rubySpace")
    {
        ioIn >> m_rubySpace;
    }
    else if (inTagStr == "brightness")
    {
        ioIn >> m_brightness;
    }
    else if (inTagStr == "showFps")
    {
        ioIn >> m_showFps;
    }
    else if (inTagStr == "scannerOn")
    {
        ioIn >> m_scannerOn;
    }
    else if (inTagStr == "playerTargetID")
    {
        ioIn >> m_playerTargetID;
    }
    else if (inTagStr == "khaziCount")
    {
        ioIn >> m_khaziCount;
    }
    else if (inTagStr == "khaziRedCount")
    {
        ioIn >> m_khaziRedCount;
    }
    else if (inTagStr == "khaziBlueCount")
    {
        ioIn >> m_khaziBlueCount;
    }
    else if (inTagStr == "khaziRedTotal")
    {
        ioIn >> m_khaziRedTotal;
    }
    else if (inTagStr == "khaziBlueTotal")
    {
        ioIn >> m_khaziBlueTotal;
    }
    else if (inTagStr == "jammerCount")
    {
        ioIn >> m_jammerCount;
    }
    else if (inTagStr == "playerCount")
    {
        ioIn >> m_playerCount;
    }
    else if (inTagStr == "damageIcons")
    {
        ioIn >> m_damageIcons;
    }
    else if (MushGameVolatileData::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisVolatileData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameVolatileData::AutoXMLPrint(ioOut);
    ioOut.TagSet("decoList");
    ioOut << m_decoList;
    ioOut.TagSet("worldList");
    ioOut << m_worldList;
    ioOut.TagSet("aRenderMesh");
    ioOut << m_aRenderMesh;
    ioOut.TagSet("rubySpace");
    ioOut << m_rubySpace;
    ioOut.TagSet("brightness");
    ioOut << m_brightness;
    ioOut.TagSet("showFps");
    ioOut << m_showFps;
    ioOut.TagSet("scannerOn");
    ioOut << m_scannerOn;
    ioOut.TagSet("playerTargetID");
    ioOut << m_playerTargetID;
    ioOut.TagSet("khaziCount");
    ioOut << m_khaziCount;
    ioOut.TagSet("khaziRedCount");
    ioOut << m_khaziRedCount;
    ioOut.TagSet("khaziBlueCount");
    ioOut << m_khaziBlueCount;
    ioOut.TagSet("khaziRedTotal");
    ioOut << m_khaziRedTotal;
    ioOut.TagSet("khaziBlueTotal");
    ioOut << m_khaziBlueTotal;
    ioOut.TagSet("jammerCount");
    ioOut << m_jammerCount;
    ioOut.TagSet("playerCount");
    ioOut << m_playerCount;
    ioOut.TagSet("damageIcons");
    ioOut << m_damageIcons;
}
//%outOfLineFunctions } 98ce20gAsqUaW1he3IFQhQ
