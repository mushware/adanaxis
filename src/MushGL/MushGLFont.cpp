//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLFont.cpp
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
//%Header } D0XSpVk5PaoaWCkqXIb5MA
/*
 * $Id: MushGLFont.cpp,v 1.9 2006/10/17 20:43:01 southa Exp $
 * $Log: MushGLFont.cpp,v $
 * Revision 1.9  2006/10/17 20:43:01  southa
 * Dashboard work
 *
 * Revision 1.8  2006/10/09 16:00:16  southa
 * Intern generation
 *
 * Revision 1.7  2006/08/01 17:21:32  southa
 * River demo
 *
 * Revision 1.6  2006/07/25 20:31:03  southa
 * Scanner work
 *
 * Revision 1.5  2006/07/25 13:30:57  southa
 * Initial scanner work
 *
 * Revision 1.4  2006/07/08 16:05:57  southa
 * Ruby menus and key handling
 *
 * Revision 1.3  2006/07/02 21:08:54  southa
 * Ruby menu work
 *
 * Revision 1.2  2006/07/02 09:43:27  southa
 * MushGLFont work
 *
 * Revision 1.1  2006/04/21 00:10:43  southa
 * MushGLFont ruby module
 *
 */

#include "MushGLFont.h"

#include "MushGLState.h"
#include "MushGLUtil.h"

#include "mushMushRuby.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushGLFont);

MushGLFont::MushGLFont() :
    m_colour(1,1,1,1)
{
}

void
MushGLFont::RenderSymbolAtSize(const Mushware::U32 inValue, const Mushware::t4Val& inCoords,
                               const Mushware::t2Val& inSize) const
{
    MushGLState::Sgl().TextureEnable2D(0); // Enable texture 0
    m_textureRef.WRef().Bind();
    
    t4U32 texSize = m_textureRef.WRef().Size();
    
    MushGLUtil::ColourSet(m_colour);
    
    tVal xSize = inSize.X();
    tVal ySize = inSize.Y();
    
    tVal xPos = inCoords.X() - xSize/2;
    tVal yPos = inCoords.Y() - ySize/2;
    tVal zPos = inCoords.Z();
    tVal wPos = inCoords.W();
    
    tVal uScale = m_extent.X() / texSize.X();
    tVal vScale = m_extent.Y() / texSize.Y();
    
    tVal uPos = (inValue % m_divide.X()) * uScale;
    tVal vPos = (1 + inValue / m_divide.X()) * vScale;
    
    // Already expect to be in kRenderState2D    
    glBegin(GL_QUADS);
    
    glTexCoord2f(uPos, vPos);
    glVertex4f(xPos, yPos, zPos, wPos);
    glTexCoord2f(uPos + uScale, vPos);
    glVertex4f(xPos + xSize, yPos, zPos, wPos);
    glTexCoord2f(uPos + uScale, vPos - vScale);
    glVertex4f(xPos + xSize, yPos + ySize, zPos, wPos);
    glTexCoord2f(uPos, vPos - vScale);
    glVertex4f(xPos, yPos + ySize, zPos, wPos);
    
    glEnd();
}

void
MushGLFont::RenderSymbolAtSizeProportion(const Mushware::U32 inValue, const Mushware::t4Val& inCoords,
                               const Mushware::t2Val& inSize, const Mushware::t2Val& inProp) const
{
    MushGLState::Sgl().TextureEnable2D(0); // Enable texture 0
    m_textureRef.WRef().Bind();
    
    t4U32 texSize = m_textureRef.WRef().Size();
    
    MushGLUtil::ColourSet(m_colour);
    
    tVal xSize = inSize.X();
    tVal ySize = inSize.Y();
    
    tVal xPos = inCoords.X() - xSize/2;
    tVal yPos = inCoords.Y() - ySize/2;
    tVal zPos = inCoords.Z();
    tVal wPos = inCoords.W();
    
    tVal uScale = m_extent.X() / texSize.X();
    tVal vScale = m_extent.Y() / texSize.Y();
    
    tVal uPos = (inValue % m_divide.X()) * uScale;
    tVal vPos = (1 + inValue / m_divide.X()) * vScale;
    
    xSize *= inProp.X();
    ySize *= inProp.Y();
    uScale *= inProp.X();
    vScale *= inProp.Y();
    
    // Already expect to be in kRenderState2D    
    glBegin(GL_QUADS);
    
    glTexCoord2f(uPos, vPos);
    glVertex4f(xPos, yPos, zPos, wPos);
    glTexCoord2f(uPos + uScale, vPos);
    glVertex4f(xPos + xSize, yPos, zPos, wPos);
    glTexCoord2f(uPos + uScale, vPos - vScale);
    glVertex4f(xPos + xSize, yPos + ySize, zPos, wPos);
    glTexCoord2f(uPos, vPos - vScale);
    glVertex4f(xPos, yPos + ySize, zPos, wPos);
    
    glEnd();
}

void
MushGLFont::RenderSymbolAtSizeAngle(const Mushware::U32 inValue, const Mushware::t4Val& inCoords,
                                    const Mushware::t2Val& inSize, Mushware::tVal inAngle) const
{
    MushGLState::Sgl().TextureEnable2D(0); // Enable texture 0
    m_textureRef.WRef().Bind();
    
    t4U32 texSize = m_textureRef.WRef().Size();
    
    MushGLUtil::ColourSet(m_colour);
    
    tVal xSize = inSize.X();
    tVal ySize = inSize.Y();
    
    tVal xPos = inCoords.X();
    tVal yPos = inCoords.Y();
    tVal zPos = inCoords.Z();
    tVal wPos = inCoords.W();
    
    tVal uScale = m_extent.X() / texSize.X();
    tVal vScale = m_extent.Y() / texSize.Y();
    
    tVal uPos = (inValue % m_divide.X()) * uScale;
    tVal vPos = (1 + inValue / m_divide.X()) * vScale;
    
    tVal uTweak = 0;
    tVal vTweak = 0;
    
    // Already expect to be in kRenderState2D    
    glBegin(GL_QUADS);
    
    tVal xSize2 = xSize/sqrt(2.0);
    tVal ySize2 = ySize/sqrt(2.0);
    
    glTexCoord2f(uPos + uTweak, vPos - vTweak);
    glVertex4f(xPos + xSize2 * cos(inAngle + 5*M_PI/4), yPos + ySize2 * sin(inAngle + 5*M_PI/4), zPos, wPos);
    glTexCoord2f(uPos + uScale - uTweak, vPos - vTweak);
    glVertex4f(xPos + xSize2 * cos(inAngle + 7*M_PI/4), yPos + ySize2 * sin(inAngle + 7*M_PI/4), zPos, wPos);
    glTexCoord2f(uPos + uScale - uTweak, vPos - vScale + vTweak);
    glVertex4f(xPos + xSize2 * cos(inAngle + 1*M_PI/4), yPos + ySize2 * sin(inAngle + 1*M_PI/4), zPos, wPos);
    glTexCoord2f(uPos + uTweak, vPos - vScale + vTweak);
    glVertex4f(xPos + xSize2 * cos(inAngle + 3*M_PI/4), yPos + ySize2 * sin(inAngle + 3*M_PI/4), zPos, wPos);
    
    glEnd();
}

void
MushGLFont::RenderAtSize(const std::string& inStr, const Mushware::t2Val& inCoords,
                         const Mushware::t2Val& inSize) const
{
    U32 strSize = inStr.size();

    MushGLState::Sgl().TextureEnable2D(0); // Enable texture 0
    m_textureRef.WRef().Bind();
    
    t4U32 texSize = m_textureRef.WRef().Size();
    
    MushGLUtil::ColourSet(m_colour);
    
    // Already expect to be in kRenderState2D    
    glBegin(GL_QUADS);
    
    tVal xSize = inSize.X();
    tVal ySize = inSize.Y();
    
    tVal xPos = inCoords.X();
    tVal yPos = inCoords.Y() - ySize/2;
    tVal uScale = m_extent.X() / texSize.X();
    tVal vScale = m_extent.Y() / texSize.Y();
    
    // Move half a pixel away from the edges of the character tile
    tVal uTweak = 0.5 / texSize.X();
    tVal vTweak = 0.5 / texSize.Y();
    
    for (U32 i=0; i < strSize; ++i)
    {
        U32 charValue = inStr[i];
        
        if (charValue < 32)
        {
            // Control character
        }
        else
        {
            if (charValue != 32) // Don't render spaces
            {
                charValue -= 32;
            
                tVal uPos = (charValue % m_divide.X()) * uScale;
                tVal vPos = (1 + charValue / m_divide.X()) * vScale;
                
                glTexCoord2f(uPos + uTweak , vPos - vTweak);
                glVertex2f(xPos, yPos);
                glTexCoord2f(uPos + uScale - uTweak, vPos - vTweak);
                glVertex2f(xPos + xSize, yPos);
                glTexCoord2f(uPos + uScale - uTweak, vPos - vScale + vTweak);
                glVertex2f(xPos + xSize, yPos + ySize);
                glTexCoord2f(uPos + uTweak, vPos - vScale + vTweak);
                glVertex2f(xPos, yPos + ySize);
            }
            xPos += xSize;
        }
    }
    glEnd();
}

void
MushGLFont::Render(const std::string& inStr) const
{
    RenderAtSize(inStr, t2Val(0,0), m_size);
}

void
MushGLFont::RenderAt(const std::string& inStr, const Mushware::t2Val& inCoords) const
{
    RenderAtSize(inStr, inCoords, m_size);
}

//%outOfLineFunctions {

const char *MushGLFont::AutoName(void) const
{
    return "MushGLFont";
}

MushcoreVirtualObject *MushGLFont::AutoClone(void) const
{
    return new MushGLFont(*this);
}

MushcoreVirtualObject *MushGLFont::AutoCreate(void) const
{
    return new MushGLFont;
}

MushcoreVirtualObject *MushGLFont::AutoVirtualFactory(void)
{
    return new MushGLFont;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLFont", MushGLFont::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLFont::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "textureRef=" << m_textureRef << ", ";
    ioOut << "divide=" << m_divide << ", ";
    ioOut << "extent=" << m_extent << ", ";
    ioOut << "size=" << m_size << ", ";
    ioOut << "colour=" << m_colour;
    ioOut << "]";
}
bool
MushGLFont::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "textureRef")
    {
        ioIn >> m_textureRef;
    }
    else if (inTagStr == "divide")
    {
        ioIn >> m_divide;
    }
    else if (inTagStr == "extent")
    {
        ioIn >> m_extent;
    }
    else if (inTagStr == "size")
    {
        ioIn >> m_size;
    }
    else if (inTagStr == "colour")
    {
        ioIn >> m_colour;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLFont::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("textureRef");
    ioOut << m_textureRef;
    ioOut.TagSet("divide");
    ioOut << m_divide;
    ioOut.TagSet("extent");
    ioOut << m_extent;
    ioOut.TagSet("size");
    ioOut << m_size;
    ioOut.TagSet("colour");
    ioOut << m_colour;
}
//%outOfLineFunctions } IbezCX7S8o8eqM5hb6Jsbg
