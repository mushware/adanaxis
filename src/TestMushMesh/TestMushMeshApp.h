//%includeGuardStart {
#ifndef TESTMUSHMESHAPP_H
#define TESTMUSHMESHAPP_H
//%includeGuardStart } Vy7fiBIHVuBaJm7VyhbBSg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshApp.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ena/NJpozGY6u8k6tjjR6Q
/*
 * $Id: TestMushMeshApp.h,v 1.4 2003/09/17 19:40:39 southa Exp $
 * $Log: TestMushMeshApp.h,v $
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
