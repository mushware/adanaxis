#ifndef GRAPHWRANGLER_H
#define GRAPHWRANGLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GraphWrangler.h,v 1.8 2002/10/22 20:42:08 southa Exp $
 * $Log: GraphWrangler.h,v $
 * Revision 1.8  2002/10/22 20:42:08  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 08:56:30  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:52  southa
 * Conditioned source
 *
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

    Mushware::U32 PredominantColumnColour(Mushware::U32 inX);
    void ReplaceInColumn(Mushware::U32 inX, Mushware::U32 inSrcCol, Mushware::U32 inDestCol);

    Mushware::U32 Pixel(Mushware::U32 inX, Mushware::U32 inY);
    void SetPixel(Mushware::U32 inX, Mushware::U32 inY, Mushware::U32 inCol);

private:        
    State m_state;
    GLTexture& m_tex;
    Mushware::U32 m_width;
    Mushware::U32 m_height;
    Mushware::U32 m_hbytes;
    Mushware::U32 *m_dataPtr;
    Mushware::U32 m_vertAxis;
    Mushware::U32 m_horizAxis;
};
#endif
