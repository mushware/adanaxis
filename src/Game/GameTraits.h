/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameTraits : public CorePickle, protected CoreXMLHandler
{
public:
    GameTraits(): m_traitsValid(false) {}
    virtual ~GameTraits() {}
    void Verify(void);
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    
protected:
    U32 NumberOfTraitsGet(void) const;
    const GameTraits& GetTraits(U32 inIndex) const;
    const string TraitsNameGet(void) const;

    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);    
    
private:

    void HandleBaseStart(CoreXML& inXML);
    void HandleBaseEnd(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef map<string, void (GameTraits::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;

    void RebuildTraits(void) const;
        
    vector<string> m_baseNames;
    mutable string m_failMessage;
    mutable bool m_traitsValid;
    mutable vector<GameTraits *> m_baseTraits;
};
