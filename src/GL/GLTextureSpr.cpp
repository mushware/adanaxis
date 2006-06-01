//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureSpr.cpp
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
//%Header } auUg+I2KBEN9kX9Wz3xLKw
/*
 * $Id: GLTextureSpr.cpp,v 1.27 2005/05/19 13:02:00 southa Exp $
 * $Log: GLTextureSpr.cpp,v $
 * Revision 1.27  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.26  2004/09/27 22:42:08  southa
 * MSVC compilation fixes
 *
 * Revision 1.25  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.24  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.23  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.22  2003/08/21 23:08:32  southa
 * Fixed file headers
 *
 * Revision 1.21  2003/02/05 16:19:45  southa
 * Build fixes
 *
 * Revision 1.20  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.19  2003/01/12 17:32:51  southa
 * Mushcore work
 *
 * Revision 1.18  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.17  2003/01/09 14:56:59  southa
 * Created Mushcore
 *
 * Revision 1.16  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.15  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.14  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.13  2002/08/27 08:56:21  southa
 * Source conditioning
 *
 * Revision 1.12  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.11  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 * Revision 1.10  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.9  2002/07/02 15:48:30  southa
 * Floor map designer
 *
 * Revision 1.8  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.7  2002/05/28 16:37:39  southa
 * Texture references and decomposer
 *
 * Revision 1.6  2002/05/25 17:16:14  southa
 * MushcoreXML implementation
 *
 * Revision 1.5  2002/05/24 18:10:43  southa
 * MushcoreXML and game map
 *
 * Revision 1.4  2002/05/10 16:41:43  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/05/09 17:08:07  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.2  2002/03/07 22:24:34  southa
 * Command interpreter working
 *
 * Revision 1.1  2002/02/26 17:01:38  southa
 * Completed Sprite loader
 *
 */

#include "GLTextureSpr.h"
#include "mushMushcore.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLTextureSpr::Palette *GLTextureSpr::m_palette=NULL;

GLTextureSpr::GLTextureSpr(const string& inFilename)
{
    throw(MushcoreFileFail(inFilename, "Could not open file - unsupported format (RiscOS)"));
#if 0
    MushcoreStreamUtil sUtil;
    FilenameSet(inFilename);

    ifstream in(MushcoreUtil::TranslateFilename(inFilename).c_str());

    if (!in) throw(MushcoreFileFail(inFilename, "Could not open file"));
    U32 numSprites=sUtil.LittleEndianU32Get(in);
    IFTEXTESTING(U32 offsetFirst=sUtil.LittleEndianU32Get(in);)
    IFTEXTESTING(U32 offsetFree=sUtil.LittleEndianU32Get(in);)

    IFTEXTESTING(cerr << "(hex)" << hex << endl);
    IFTEXTESTING(cerr << "numSprites=" << numSprites << ", ");
    IFTEXTESTING(cerr << "offsetFirst=" << offsetFirst << ", ");
    IFTEXTESTING(cerr << "offsetFree=" << offsetFree);
    IFTEXTESTING(cerr << endl);
    
    if (numSprites > 0xffff) throw (MushcoreFileFail(inFilename, "Corrupt sprite file - first word insane"));

    for (U32 spriteCtr=0; spriteCtr<numSprites; ++spriteCtr)
    {
        sUtil.ZeroIndex(0);
        U32 offsetNext=sUtil.LittleEndianU32Get(in);
        IFTEXTESTING(cerr << "Image " << spriteCtr << " [");
        IFTEXTESTING(cerr << "offsetNext=" << offsetNext << ", ");
        string name;
        bool addIt=true;
        for (int i=0; i<12; ++i)
        {
            U8 ch=sUtil.U8Get(in);
            if (ch=='\0') addIt=false;
            if (addIt) name+=ch;
        }
        U32 wordWidth=sUtil.LittleEndianU32Get(in)+1;
        U32 height=sUtil.LittleEndianU32Get(in)+1;
        IFTEXTESTING(U32 firstPixel=sUtil.LittleEndianU32Get(in);)
        U32 lastPixel=sUtil.LittleEndianU32Get(in);
        U32 dataOffset=sUtil.LittleEndianU32Get(in);
        IFTEXTESTING(U32 maskOffset=sUtil.LittleEndianU32Get(in);)
        GLSpriteModeRO mode(sUtil.LittleEndianU32Get(in));

        IFTEXTESTING(cerr << "name='" << name << "', ");
        IFTEXTESTING(cerr << "wordWidth=" << wordWidth << ", ");
        IFTEXTESTING(cerr << "height=" << height << ", ");
        IFTEXTESTING(cerr << "firstPixel=" << firstPixel << ", ");
        IFTEXTESTING(cerr << "lastPixel=" << lastPixel << ", ");
        IFTEXTESTING(cerr << "dataOffset=" << dataOffset << ", ");
        IFTEXTESTING(cerr << "maskOffset=" << maskOffset << ", ");
        IFTEXTESTING(cerr << "mode=" << mode.Value());
        IFTEXTESTING(cerr << "]");

        if (!mode.Valid()) throw (MushcoreFileFail(inFilename, "Unsupported sprite mode"));

        U32 width=(wordWidth*32-(31-lastPixel))/mode.BitsPerPixel();

        IFTEXTESTING(cerr << "[");
        IFTEXTESTING(cerr << "width=" << width << ", ");
        IFTEXTESTING(cerr << "bitsPerPixel=" << mode.BitsPerPixel() << ", ");
        IFTEXTESTING(cerr << "pixelDouble=" << mode.PixelDouble() << "]" << endl);

        U32 inpuU32=(height*width*mode.BitsPerPixel()+7)/8;

        U8 inputData[inpuU32];
        
        sUtil.ConsumeToIndex(in, 0, dataOffset);
        sUtil.Get(in, inputData, inpuU32);
        
        U32 pixelMult=mode.PixelDouble()?2:1;
        U32 u32Size=width*height;

        if (mode.PixelDouble()) u32Size *= pixelMult*pixelMult;
        
        GLTextureDef def(new U32[u32Size]);

        def.WidthSet(width*pixelMult);
        def.HeightSet(height*pixelMult);
        def.PixelFormatSet(GL_RGBA);
        def.PixelTypeSet(GL_UNSIGNED_BYTE);

        if (m_palette==NULL) GeneratePalette();
        
        for (int y=0; y<def.Height(); ++y)
        {
            U32 *outputPtr;
            U8 *inputPtr;
            inputPtr=&inputData[((def.Height()-1-y)/pixelMult) * def.Width()/pixelMult];
            outputPtr=&def.DataPtr()[y*def.Width()];

            for (U32 x=0; x<width; ++x)
            {
                U8 colIndex=*inputPtr++;
                for (U32 outputCtr=0; outputCtr<pixelMult; ++outputCtr)
                {
                    // Pack data into output buffer in RGB order
                    *outputPtr++ =
                        m_palette[colIndex].red << 24 |
                        m_palette[colIndex].green << 16 |
                        m_palette[colIndex].blue << 8 |
                        m_palette[colIndex].alpha;
                }
            }
            if (outputPtr > def.DataPtr() + u32Size)
            {
                throw(MushcoreFileFail(inFilename, "Pointer error"));
            }
        }
        // This step adds a second reference to the def which stops its memory being
        // freed as it goes out of scope

        U32 sprIndex=atoi(name.c_str());
        if (sprIndex != 0 || name=="0")
        {
            if (sprIndex > 0xffff)
            {
                throw(MushcoreFileFail(inFilename, "Sprite number too large"));
            }
            if (TextureDefValid(sprIndex))
            {
                throw(MushcoreFileFail(inFilename, "Numbering fault - one sprite overwrites another"));
            }
            AddTextureDef(def, sprIndex);
        }
        sUtil.ConsumeToIndex(in, 0, offsetNext);
        if (in.eof()) throw(MushcoreFileFail(inFilename, "Unexpected EOF"));
        if (!in.good()) throw(MushcoreFileFail(inFilename, "Fault reading file"));
    }
    IFTEXTESTING(cerr << "(dec)" << dec << endl);
#endif
}

void
GLTextureSpr::GeneratePalette(void)
{
    assert(m_palette==NULL);
    m_palette=new Palette[256];
    for (U32 i=0; i<256; i++)
    {
        m_palette[i].red   = 0x11 * (((i>>1) & 8) | (i&7));
        m_palette[i].green = 0x11 * (((i>>3) & 0xC) | (i&3));
        m_palette[i].blue = 0x11 * (((i>>4) & 8) | ((i>>1) & 4) | (i&3));
        m_palette[i].alpha = 0xff;
    }
}

const char *
GLTextureSpr::FiletypeName(void) const
{
    return "RISCOS Sprite";
}
