#ifndef GAMEGRAPHICMODEL_H
#define GAMEGRAPHICMODEL_H
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
 * $Id: GameGraphicModel.h,v 1.7 2002/12/20 13:17:40 southa Exp $
 * $Log: GameGraphicModel.h,v $
 * Revision 1.7  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/11/24 23:18:23  southa
 * Added type name accessor to CorePickle
 *
 * Revision 1.5  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.4  2002/10/15 14:02:31  southa
 * Mode changes
 *
 * Revision 1.3  2002/10/14 15:13:40  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.2  2002/10/12 17:34:21  southa
 * Wall edges
 *
 * Revision 1.1  2002/10/12 11:22:21  southa
 * GraphicModel work
 *
 */

#include "GameGraphic.h"
#include "mushGL.h"

class GameGraphicModel: public GameGraphic
{
public:
    GameGraphicModel(): m_listContext(0) {}
    virtual ~GameGraphicModel();
    virtual void Render(void);
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void HandleGraphicEnd(CoreXML& inXML);
    void HandleTextureEnd(CoreXML& inXML);
    void HandleFacetsStart(CoreXML& inXML);
    void HandleFacetsEnd(CoreXML& inXML);
    void HandleOffsetEnd(CoreXML& inXML);
    void HandleFacetOffsetEnd(CoreXML& inXML);
    void HandleVertexEnd(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleFacets,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef std::map<string, void (GameGraphicModel::*)(CoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;
    // End of XML stuff
    
    class FacetDef
    {
    public:
        GLenum type;
        GLTextureRef texRef;
        GLArray<GLVector, GLfloat[3]> vertices;
        GLArray<GLPoint, GLfloat[2]> texCoords;
        GLArray<GLVector, GLfloat[3]> normals;
    };

    GLVector m_positionOffset;
    GLPoint m_texCoordOffset;
    GLVector m_facetPositionOffset;
    GLPoint m_facetTexCoordOffset;
    GLTextureRef m_currentTexRef;
    
    std::vector<FacetDef> m_facets;
    std::vector<GLuint> m_listName;
    
    Mushware::U32 m_listContext;
};

inline std::ostream& operator<<(std::ostream &inOut, const GameGraphicModel& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
