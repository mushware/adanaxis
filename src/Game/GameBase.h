/*
 * $Id: GameBase.h,v 1.2 2002/05/10 16:39:34 southa Exp $
 * $Log: GameBase.h,v $
 * Revision 1.2  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "mushCore.h"

class GameBase
{
public:
    virtual void Process(bool& outDoQuit, bool& outRedraw) = 0;
    virtual void Display(void) = 0;

private:

};
