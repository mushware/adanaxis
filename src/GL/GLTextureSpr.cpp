/*
 * $Id: GLTextureSpr.cpp,v 1.6 2002/05/25 17:16:14 southa Exp $
 * $Log: GLTextureSpr.cpp,v $
 * Revision 1.6  2002/05/25 17:16:14  southa
 * CoreXML implementation
 *
 * Revision 1.5  2002/05/24 18:10:43  southa
 * CoreXML and game map
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
#include "mushCore.h"

GLTextureSpr::Palette *GLTextureSpr::m_palette=NULL;

GLTextureSpr::GLTextureSpr(const string& inFilename)
{
    StreamUtil sUtil;
    FilenameSet(inFilename);

    u8ifstream in(CoreUtil::TranslateFilename(inFilename).c_str());

    if (!in) throw(LoaderFail(inFilename, "Could not open file"));
    U32 numSprites=sUtil.LittleEndianU32Get(in);
    IFTEXTESTING(U32 offsetFirst=sUtil.LittleEndianU32Get(in);)
    IFTEXTESTING(U32 offsetFree=sUtil.LittleEndianU32Get(in);)

    IFTEXTESTING(cerr << "(hex)" << hex << endl);
    IFTEXTESTING(cerr << "numSprites=" << numSprites << ", ");
    IFTEXTESTING(cerr << "offsetFirst=" << offsetFirst << ", ");
    IFTEXTESTING(cerr << "offsetFree=" << offsetFree);
    IFTEXTESTING(cerr << endl);
    
    if (numSprites > 0xffff) throw (LoaderFail(inFilename, "Corrupt sprite file - first word insane"));

    for (tSize spriteCtr=0; spriteCtr<numSprites; ++spriteCtr)
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

        if (!mode.Valid()) throw (LoaderFail(inFilename, "Unsupported sprite mode"));

        U32 width=(wordWidth*32-(31-lastPixel))/mode.BitsPerPixel();

        IFTEXTESTING(cerr << "[");
        IFTEXTESTING(cerr << "width=" << width << ", ");
        IFTEXTESTING(cerr << "bitsPerPixel=" << mode.BitsPerPixel() << ", ");
        IFTEXTESTING(cerr << "pixelDouble=" << mode.PixelDouble() << "]" << endl);

        tSize inputSize=(height*width*mode.BitsPerPixel()+7)/8;

        U8 inputData[inputSize];
        
        sUtil.ConsumeToIndex(in, 0, dataOffset);
        sUtil.Get(in, inputData, inputSize);
        
        tSize pixelMult=mode.PixelDouble()?2:1;
        tSize u32Size=width*height;

        if (mode.PixelDouble()) u32Size *= pixelMult*pixelMult;
        
        TextureDef def(new U32[u32Size]);

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

            for (tSize x=0; x<width; ++x)
            {
                U8 colIndex=*inputPtr++;
                for (tSize outputCtr=0; outputCtr<pixelMult; ++outputCtr)
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
                throw(LoaderFail(inFilename, "Pointer error"));
            }
        }
        // This step adds a second reference to the def which stops its memory being
        // freed as it goes out of scope

        U32 sprIndex=atoi(name.c_str());
        if (sprIndex != 0 || name=="0")
        {
            if (sprIndex > 0xffff)
            {
                throw(LoaderFail(inFilename, "Sprite number too large"));
            }
            if (TextureDefValid(sprIndex))
            {
                throw(LoaderFail(inFilename, "Numbering fault - one sprite overwrites another"));
            }
            AddTextureDef(def, sprIndex);
        }
        sUtil.ConsumeToIndex(in, 0, offsetNext);
        if (in.eof()) throw(LoaderFail(inFilename, "Unexpected EOF"));
        if (!in.good()) throw(LoaderFail(inFilename, "Fault reading file"));
    }
    IFTEXTESTING(cerr << "(dec)" << dec << endl);
}

void
GLTextureSpr::GeneratePalette(void)
{
    assert(m_palette==NULL);
    m_palette=new Palette[256];
    for (tSize i=0; i<256; i++)
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
