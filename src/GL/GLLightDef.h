//%includeGuardStart {
#ifndef GLLIGHTDEF_H
#define GLLIGHTDEF_H
//%includeGuardStart } 8SxWLGzkk7ft/b9Ta5Xc3Q
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLLightDef.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } LvKekWc1xqJ+cO75GE9lgg

/*
 * $Id: GLLightDef.h,v 1.17 2005/05/19 13:01:59 southa Exp $
 * $Log: GLLightDef.h,v $
 * Revision 1.17  2005/05/19 13:01:59  southa
 * Mac release work
 *
 * Revision 1.16  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.15  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.14  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.13  2003/08/21 23:08:22  southa
 * Fixed file headers
 *
 * Revision 1.12  2003/02/05 16:19:45  southa
 * Build fixes
 *
 * Revision 1.11  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.10  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.8  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/11/24 23:18:04  southa
 * Added type name accessor to MushcorePickle
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
#include "mushMushcore.h"

class GLLightDef : public MushcorePickle, protected MushcoreXMLHandler
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
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void HandleOffsetEnd(MushcoreXML& inXML);
    void HandlePowerEnd(MushcoreXML& inXML);
    void HandleColourEnd(MushcoreXML& inXML);
    void HandleAmbientEnd(MushcoreXML& inXML);
    void HandleDiffuseEnd(MushcoreXML& inXML);
    void HandleSpecularEnd(MushcoreXML& inXML);
    void HandleCutoffEnd(MushcoreXML& inXML);
    void HandleDirectionEnd(MushcoreXML& inXML);
    void HandleExponentEnd(MushcoreXML& inXML);
    void HandleConstantEnd(MushcoreXML& inXML);
    void HandleLinearEnd(MushcoreXML& inXML);
    void HandleQuadraticEnd(MushcoreXML& inXML);
    void HandleLightEnd(MushcoreXML& inXML);    
    void NullHandler(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef std::map<std::string, void (GLLightDef::*)(MushcoreXML& inXML)> ElementFunctionMap;
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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
