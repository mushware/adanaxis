/*
 * $Id$
 * $Log$
 */

#include "GLTest.hp"

#include "GLStandard.hp"
#include "CoreTest.hp"
#include "GLTest1AppHandler.hp"

void
GLTest::Test1(const string& inStr)
{
    CoreAppHandler::Instance().Mutate(new GLTest1AppHandler);
}