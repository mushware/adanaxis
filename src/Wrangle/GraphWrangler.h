#ifndef GRAPHWRANGLER_H
#define GRAPHWRANGLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/



/*
 * $Id: GraphWrangler.h,v 1.5 2002/07/06 18:04:20 southa Exp $
 * $Log: GraphWrangler.h,v $
 * Revision 1.5  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:09  southa
 * Build process fixes
 *
 * Revision 1.3  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 * Revision 1.2  2002/05/24 16:24:12  southa
 * Config and typenames
 *
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

    void Process(bool& outRedraw);

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
#endif
