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
 * $Id$
 * $Log$
 */

#include "GameGraphic.h"
#include "mushGL.h"

class GameGraphicModel: public GameGraphic
{
public:
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
        GLTextureRef texRef;
        GLArray<GLVector, GLfloat[3]> vertices;
        GLArray<GLPoint, GLfloat[2]> texCoords;
    };
    
    GLVector m_positionOffset;
    GLPoint m_texCoordOffset;
    GLTextureRef m_currentTexRef;
    
    vector<FacetDef> m_facets;
};

inline ostream& operator<<(ostream &inOut, const GameGraphicModel& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
