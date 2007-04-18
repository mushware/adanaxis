//%includeGuardStart {
#ifndef TESTMUSHMESHAPP_H
#define TESTMUSHMESHAPP_H
//%includeGuardStart } Vy7fiBIHVuBaJm7VyhbBSg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshApp.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } NMaWzJZhFpqDwjlCnSxigg
/*
 * $Id: TestMushMeshApp.h,v 1.4 2006/06/01 15:40:01 southa Exp $
 * $Log: TestMushMeshApp.h,v $
 * Revision 1.4  2006/06/01 15:40:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.2  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/14 13:07:26  southa
 * MushMesh vector creation
 *
 */

#include "TestMushMeshStandard.h"

class TestMushMeshApp : public MushcoreSingleton<TestMushMeshApp>
{
public:
    void EnterInstance(void);
    void RunTest(const std::string& inCommandStr, const std::string& inNameStr);
    static void Enter(void);
    static void FailureAdd(const std::string& inStr);
    static void PassAdd(const std::string& inStr);
    static void FailuresPrint(void);
    
private:
    typedef std::vector<std::string> tFails;
    static Mushware::U32 m_passCount;
    static tFails m_fails;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
