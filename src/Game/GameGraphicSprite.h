//%includeGuardStart {
#ifndef GAMEGRAPHICSPRITE_H
#define GAMEGRAPHICSPRITE_H
//%includeGuardStart } UevdRnMEWVUbLjVkcKRLww
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameGraphicSprite.h
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
//%Header } 3Hwb9+XAsYyuylg3fxNNcg
/*
 * $Id: GameGraphicSprite.h,v 1.19 2006/06/01 15:38:58 southa Exp $
 * $Log: GameGraphicSprite.h,v $
 * Revision 1.19  2006/06/01 15:38:58  southa
 * DrawArray verification and fixes
 *
 * Revision 1.18  2005/05/19 13:02:02  southa
 * Mac release work
 *
 * Revision 1.17  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.16  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.15  2003/08/21 23:08:46  southa
 * Fixed file headers
 *
 * Revision 1.14  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.13  2003/01/09 14:57:02  southa
 * Created Mushcore
 *
 * Revision 1.12  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.11  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.10  2002/11/24 23:18:23  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.9  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.8  2002/10/08 21:44:10  southa
 * 3D maps
 *
 * Revision 1.7  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/08 14:22:03  southa
 * Rotated desks
 *
 * Revision 1.4  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/04 20:27:37  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.1  2002/06/04 17:02:11  southa
 * More work
 *
 */

#include "GameGraphic.h"
#include "mushGL.h"

class GameGraphicSprite: public GameGraphic
{
public:

    virtual void Render(void);
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void HandleGraphicEnd(MushcoreXML& inXML);
    void HandleNameEnd(MushcoreXML& inXML);
    void HandleRectEnd(MushcoreXML& inXML);
    void HandleOffsetEnd(MushcoreXML& inXML);
    void HandleRotateEnd(MushcoreXML& inXML);
    void NullHandler(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef std::map<std::string, void (GameGraphicSprite::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;
    
    GLTextureRef m_texRef;
    GLRectangle m_rectangle;
    Mushware::tVal m_rotation;
    GLVector m_offset;
};

inline std::ostream& operator<<(std::ostream &inOut, const GameGraphicSprite& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
