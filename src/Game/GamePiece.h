/*
 * $Id$
 * $Log$
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
