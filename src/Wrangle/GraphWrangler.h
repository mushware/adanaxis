/*
 * $Id: GraphWrangler.h,v 1.1 2002/05/10 16:40:39 southa Exp $
 * $Log: GraphWrangler.h,v $
 * Revision 1.1  2002/05/10 16:40:39  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/09 17:08:08  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.2  2002/03/24 16:35:39  southa
 * Wrangler axis finder
 *
 * Revision 1.1  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 */

#include "Wrangler.h"

class GLTexture;

class GraphWrangler : public Wrangler
{
public:
    GraphWrangler(GLTexture &inTex):
        m_state(kInit),
        m_tex(inTex),
        m_dataPtr(NULL)
        {}

    void Process(bool& outDoQuit, bool& outRedraw);

protected:
    enum State
    {
        kInit,
        kFindVertAxis,
        kFindHorizAxis,
    };     

    void Init(void);
    void FindVertAxis(void);
    void FindHorizAxis(void);

    U32 PredominantColumnColour(tSize inX);
    void ReplaceInColumn(tSize inX, U32 inSrcCol, U32 inDestCol);

    U32 Pixel(tSize inX, tSize inY);
    void SetPixel(tSize inX, tSize inY, U32 inCol);

private:        
    State m_state;
    GLTexture& m_tex;
    tSize m_width;
    tSize m_height;
    tSize m_hbytes;
    U32 *m_dataPtr;
    tSize m_vertAxis;
    tSize m_horizAxis;
};
