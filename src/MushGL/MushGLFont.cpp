//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLFont.cpp
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
//%Header } Zq+IM0uOYEygMymunhBN6w
/*
 * $Id: MushGLFont.cpp,v 1.4 2006/07/08 16:05:57 southa Exp $
 * $Log: MushGLFont.cpp,v $
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
                               const Mushware::t2Val& inSize)
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
                
                glTexCoord2f(uPos, vPos);
                glVertex2f(xPos, yPos);
                glTexCoord2f(uPos + uScale, vPos);
                glVertex2f(xPos + xSize, yPos);
                glTexCoord2f(uPos + uScale, vPos - vScale);
                glVertex2f(xPos + xSize, yPos + ySize);
                glTexCoord2f(uPos, vPos - vScale);
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
