/*
 * $Id$
 * $Log$
 */

#include "mushCore.hp"

class GameBase
{
public:
    virtual void Process(bool& outDoQuit, bool& outRedraw) = 0;

private:

};
