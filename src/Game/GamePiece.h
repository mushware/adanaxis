#ifndef GAMEPIECE_H
#define GAMEPIECE_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GamePiece.h,v 1.1 2002/06/05 15:53:26 southa Exp $
 * $Log: GamePiece.h,v $
 * Revision 1.1  2002/06/05 15:53:26  southa
 * Player and keyboard control
 *
 */

#include "mushCore.h"

class GamePiece: public CorePickle, protected CoreXMLHandler
{
public:
    GamePiece() {}
    virtual ~GamePiece() {}
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const = 0;
    virtual void Unpickle(CoreXML& inXML) = 0;
    virtual void Render(void) = 0;
    virtual void Move(void) = 0;
    virtual string TypeNameGet(void) const = 0;
    
protected:
    void UnpicklePrologue(void) {}
    void UnpickleEpilogue(void) {}

private:
};

inline ostream& operator<<(ostream &inOut, const GamePiece& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
