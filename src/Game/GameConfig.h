#ifndef GAMECONFIG_H
#define GAMECONFIG_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameConfig.h,v 1.9 2002/11/25 18:02:56 southa Exp $
 * $Log: GameConfig.h,v $
 * Revision 1.9  2002/11/25 18:02:56  southa
 * Mushware ID work
 *
 * Revision 1.8  2002/11/24 23:18:06  southa
 * Added type name accessor to CorePickle
 *
 * Revision 1.7  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.6  2002/11/14 20:24:43  southa
 * Configurable config elements
 *
 * Revision 1.5  2002/11/14 19:35:30  southa
 * Configuration work
 *
 * Revision 1.4  2002/11/14 17:29:08  southa
 * Config database
 *
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
    static CoreScalar GameConfigValueAdd(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar GameConfigStringAdd(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar GameConfigPasswordAdd(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar GameConfigBoolAdd(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static CoreScalar GameConfigSpecial(CoreCommand& ioCommand, CoreEnv& ioEnv);
    
    Mushware::U32 DisplayModeGet(void) const;
    void DisplayModeSet(Mushware::U32 inMode);
    void DisplayModeSetDefault(void);

    CoreScalar ParameterGet(const string& inName) const;
    bool ParameterExists(const string& inName) const;
    void ParameterSet(const string& inName, const CoreScalar& inValue);
    void PostDataHandle(const string& inData);
    void Update(void);
    
    virtual void Pickle(std::ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual char *TypeNameGet(void) const;
   
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

    typedef std::map<string, void (GameConfig::*)(CoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;
    // End of XML stuff
    
    void SaveToFile(void) const;

    static GameConfig *m_instance;
};
#endif
