/*
 * $Id: GameBase.h,v 1.4 2002/05/30 16:21:53 southa Exp $
 * $Log: GameBase.h,v $
 * Revision 1.4  2002/05/30 16:21:53  southa
 * Pickleable GameContract
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

#include "mushCore.h"

class GameBase
{
public:
    virtual void Process(void) = 0;
    virtual void Display(void) = 0;
    virtual void ScriptFunction(const string& inName) const = 0;

private:

};
