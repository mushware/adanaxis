#ifndef GLLIGHTDEF_H
#define GLLIGHTDEF_H

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
 * $Id: GLLightDef.h,v 1.8 2002/12/20 13:17:35 southa Exp $
 * $Log: GLLightDef.h,v $
 * Revision 1.8  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/11/24 23:18:04  southa
 * Added type name accessor to CorePickle
 *
 * Revision 1.6  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.5  2002/10/10 22:47:57  southa
 * Full light definitions
 *
 * Revision 1.4  2002/10/10 18:25:13  southa
 * Light links and test lights
 *
 * Revision 1.3  2002/10/08 17:13:16  southa
 * Tiered maps
 *
 * Revision 1.2  2002/10/08 11:58:52  southa
 * Light cache
 *
 * Revision 1.1  2002/10/06 22:09:58  southa
 * Initial lighting test
 *
*/

#include "GLColour.h"
#include "GLPoint.h"
#include "GLStandard.h"
#include "GLVector.h"
#include "mushCore.h"

class GLLightDef : public CorePickle, protected CoreXMLHandler
{
public:
    GLLightDef() {} // For vector
    virtual ~GLLightDef() {}

    const GLVector& PositionGet(void) const { return m_position; }
    const GLColour& AmbientGet(void) const { return m_ambient; }
    const GLColour& DiffuseGet(void) const { return m_diffuse; }
    const GLColour& SpecularGet(void) const { return m_specular; }
    Mushware::tVal CutoffGet(void) const { return m_cutoff; }
    const GLVector& DirectionGet(void) const { return m_direction; }
    Mushware::tVal ExponentGet(void) const { return m_exponent; }
    Mushware::tVal ConstantGet(void) const { return m_constant; }
    Mushware::tVal LinearGet(void) const { return m_linear; }
    Mushware::tVal QuadraticGet(void) const { return m_quadratic; }

    void BasePositionSet(const GLVector& inVec);
    
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
    void HandleOffsetEnd(CoreXML& inXML);
    void HandlePowerEnd(CoreXML& inXML);
    void HandleColourEnd(CoreXML& inXML);
    void HandleAmbientEnd(CoreXML& inXML);
    void HandleDiffuseEnd(CoreXML& inXML);
    void HandleSpecularEnd(CoreXML& inXML);
    void HandleCutoffEnd(CoreXML& inXML);
    void HandleDirectionEnd(CoreXML& inXML);
    void HandleExponentEnd(CoreXML& inXML);
    void HandleConstantEnd(CoreXML& inXML);
    void HandleLinearEnd(CoreXML& inXML);
    void HandleQuadraticEnd(CoreXML& inXML);
    void HandleLightEnd(CoreXML& inXML);    
    void NullHandler(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef std::map<string, void (GLLightDef::*)(CoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;

    GLVector m_basePosition;
    GLVector m_offset;
    
    GLVector m_position;
    GLColour m_ambient;
    GLColour m_diffuse;
    GLColour m_specular;
    Mushware::tVal m_cutoff;
    GLVector m_direction;
    Mushware::tVal m_exponent;
    Mushware::tVal m_constant;
    Mushware::tVal m_linear;
    Mushware::tVal m_quadratic;
};

inline std::ostream& operator<<(std::ostream &inOut, const GLLightDef& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
