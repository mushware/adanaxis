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
 * $Id: MushGLFont.cpp,v 1.2 2006/07/02 09:43:27 southa Exp $
 * $Log: MushGLFont.cpp,v $
 * Revision 1.2  2006/07/02 09:43:27  southa
 * MushGLFont work
 *
 * Revision 1.1  2006/04/21 00:10:43  southa
 * MushGLFont ruby module
 *
 */

#include "MushGLFont.h"

#include "MushGLState.h"

#include "mushMushRuby.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushGLFont);

void
MushGLFont::Render(const std::string& inStr) const
{
    U32 strSize = inStr.size();

    MushGLState::Sgl().TextureEnable2D(0); // Enable texture 0
    m_textureRef.WRef().Bind();
    
    t4U32 texSize = m_textureRef.WRef().Size();
    
    // Already expect to be in kRenderState2D    
    glBegin(GL_QUADS);
    
    tVal xSize = m_size.X();
    tVal ySize = m_size.Y();
    
    tVal xPos = 0;
    tVal yPos = -ySize/2;
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
    ioOut << "size=" << m_size;
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
}
//%outOfLineFunctions } 1z66tjSVil8HcxAD2qKSWQ
