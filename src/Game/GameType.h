/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameEvent;

class GameType : public CorePickle, protected CoreXMLHandler
{
public:
    virtual ~GameType() {}
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const = 0;
    virtual void Unpickle(CoreXML& inXML) = 0;
    virtual string TypeNameGet(void) const = 0;
    virtual void Move(void) {}
    virtual void EventHandler(GameEvent& inEvent) {}
    virtual void SequenceAdvance(void) {}
    
protected:
    void UnpicklePrologue(void) {}
    void UnpickleEpilogue(void) {}

private:
};

inline ostream& operator<<(ostream &inOut, const GameType& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
