//%includeGuardStart {
#ifndef INFERNALTEST_H
#define INFERNALTEST_H
//%includeGuardStart } lRFwbADk/cgLUmbJRpt1NA
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalTest.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 3TT2eoMsYMVPdNTCNe0Anw
/*
 * $Id: InfernalTest.h,v 1.13 2003/09/17 19:40:33 southa Exp $
 * $Log: InfernalTest.h,v $
 * Revision 1.13  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:56  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.10  2002/12/20 13:17:43  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/27 08:56:26  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.4  2002/05/24 16:23:07  southa
 * Config and typenames
 *
 * Revision 1.3  2002/05/10 22:38:22  southa
 * Checkpoint
 *
 * Revision 1.2  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "Mushcore.h"

#include "GameBase.h"

class InfernalTest: public GameBase
{
public:
    InfernalTest(): m_state(kInit) {}
    virtual ~InfernalTest() {}
    virtual void Process(bool& outDoQuit, bool& outRedraw);
    virtual void Display(void);

protected:
    enum State
    {
        kInit,
        kRunning
    };

    virtual void Init(void);
    virtual void Running(bool &outRedraw);

private:
    State m_state;
    Mushware::tVal m_playerx;
    Mushware::tVal m_playerxv;
    Mushware::tVal m_playery;
    Mushware::tVal m_playeryv;
    
    Mushware::tVal m_leftlim;
    Mushware::tVal m_rightlim;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
