//%includeGuardStart {
#ifndef INFERNALMOTION_H
#define INFERNALMOTION_H
//%includeGuardStart } M9WQa2UDypv22hagdieq3A
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalMotion.h
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
//%Header } AiDPSiINPveZLdvfKmlKsQ
/*
 * $Id: InfernalMotion.h,v 1.6 2005/05/19 13:02:05 southa Exp $
 * $Log: InfernalMotion.h,v $
 * Revision 1.6  2005/05/19 13:02:05  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.4  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.3  2003/10/04 15:32:11  southa
 * Module split
 *
 * Revision 1.2  2003/10/04 12:44:35  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:06  southa
 * File renaming
 *
 * Revision 1.13  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:49  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.10  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.9  2003/01/09 14:57:02  southa
 * Created Mushcore
 *
 * Revision 1.8  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.7  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/11/24 23:18:23  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.5  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/09 17:09:04  southa
 * InfernalDialogue added
 *
 * Revision 1.2  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/23 14:10:47  southa
 * Added InfernalMotion
 *
 */

#include "mushMushcore.h"
#include "mushGL.h"

#include "InfernalMotionSpec.h"

class InfernalMotion : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    virtual ~InfernalMotion() {}
    const InfernalMotionSpec& MotionSpecGet(void) const { return m_motionSpec; }
    void MotionSpecSet(const InfernalMotionSpec& inSpec) { m_motionSpec = inSpec; }

    void Render(void) const;

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
    void NullHandler(MushcoreXML& inXML);
    void HandleRectEnd(MushcoreXML& inXML);
    void HandlePositionEnd(MushcoreXML& inXML);
    void HandleDeltaEnd(MushcoreXML& inXML);
    void HandleMotionEnd(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef std::map<std::string, void (InfernalMotion::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;

    InfernalMotionSpec m_motionSpec;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
