#ifndef GAMEGRAPHIC_H
#define GAMEGRAPHIC_H
/*
 * $Id: GameGraphic.h,v 1.1 2002/06/04 17:02:11 southa Exp $
 * $Log: GameGraphic.h,v $
 * Revision 1.1  2002/06/04 17:02:11  southa
 * More work
 *
 */

#include "mushCore.h"

class GameGraphic : public CorePickle, protected CoreXMLHandler
{
public:
    GameGraphic() {}
    virtual ~GameGraphic() {}
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const = 0;
    virtual void Unpickle(CoreXML& inXML) = 0;
    virtual void Render(void) = 0;
    virtual string TypeNameGet(void) const = 0;    
protected:
    void UnpicklePrologue(void) {}
    void UnpickleEpilogue(void) {}
private:
};

inline ostream& operator<<(ostream &inOut, const GameGraphic& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}

#endif
