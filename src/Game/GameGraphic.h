#ifndef GAMEGRAPHIC_H
#define GAMEGRAPHIC_H
/*
 * $Id$
 * $Log$
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
    
protected:
    void UnpicklePrologue(void) {}
    void UnpickleEpilogue(void) {}
private:
};
#endif
