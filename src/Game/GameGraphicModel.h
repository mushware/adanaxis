#ifndef GAMEGRAPHICMODEL_H
#define GAMEGRAPHICMODEL_H
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
 * $Id: GameGraphicModel.h,v 1.3 2002/10/14 15:13:40 southa Exp $
 * $Log: GameGraphicModel.h,v $
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
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual string TypeNameGet(void) const {return "sprite";}
    
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

    typedef map<string, void (GameGraphicModel::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
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
    
    vector<FacetDef> m_facets;
    vector<GLuint> m_listName;
    
    U32 m_listContext;
};

inline ostream& operator<<(ostream &inOut, const GameGraphicModel& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
