//%includeGuardStart {
#ifndef GAMEGRAPHICSPRITE_H
#define GAMEGRAPHICSPRITE_H
//%includeGuardStart } UevdRnMEWVUbLjVkcKRLww
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameGraphicSprite.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } iiXUaSaqxvobNUNRtdgwFg
/*
 * $Id: GameGraphicSprite.h,v 1.15 2003/08/21 23:08:46 southa Exp $
 * $Log: GameGraphicSprite.h,v $
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
