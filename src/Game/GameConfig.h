#ifndef GAMECONFIG_H
#define GAMECONFIG_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameConfig.h,v 1.3 2002/10/22 20:42:02 southa Exp $
 * $Log: GameConfig.h,v $
 * Revision 1.3  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.2  2002/10/17 15:50:58  southa
 * Config saving, pause and quit
 *
 * Revision 1.1  2002/10/15 14:02:30  southa
 * Mode changes
 *
 */

#include "mushCore.h"

class GameConfig : public CorePickle, protected CoreXMLHandler
{
public:
    static GameConfig& Instance(void) { return *((m_instance==NULL)?m_instance=new GameConfig:m_instance); }
    
    static void Install(void);
    static CoreScalar GameConfigLoad(CoreCommand& ioCommand, CoreEnv& ioEnv);
    
    U32 DisplayModeGet(void) const;
    void DisplayModeSet(U32 inMode);
    void DisplayModeSetDefault(void);

    void PostDataHandle(const string& inData);
    
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    
protected:
    GameConfig();

    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);
    
private:
    void HandleConfigStart(CoreXML& inXML);
    void HandleConfigEnd(CoreXML& inXML);
    void HandleValueEnd(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef map<string, void (GameConfig::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;
    // End of XML stuff
    
    void SaveToFile(void) const;

    static GameConfig *m_instance;
};
#endif
