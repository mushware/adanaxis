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
 * $Id: GameConfig.h,v 1.11 2002/12/29 20:30:53 southa Exp $
 * $Log: GameConfig.h,v $
 * Revision 1.11  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.10  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/11/25 18:02:56  southa
 * Mushware ID work
 *
 * Revision 1.8  2002/11/24 23:18:06  southa
 * Added type name accessor to MushcorePickle
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

class GameConfig : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    static GameConfig& Instance(void) { return *((m_instance==NULL)?m_instance=new GameConfig:m_instance); }
    
    static void Install(void);
    static MushcoreScalar GameConfigLoad(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameConfigValueAdd(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameConfigStringAdd(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameConfigPasswordAdd(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameConfigBoolAdd(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar GameConfigSpecial(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    
    Mushware::U32 DisplayModeGet(void) const;
    void DisplayModeSet(Mushware::U32 inMode);
    void DisplayModeSetDefault(void);

    MushcoreScalar ParameterGet(const std::string& inName) const;
    bool ParameterExists(const std::string& inName) const;
    void ParameterSet(const std::string& inName, const MushcoreScalar& inValue);
    void PostDataHandle(const std::string& inData);
    void Update(void);
    
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;
   
protected:
    GameConfig();

    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);
    
private:
    void HandleConfigStart(MushcoreXML& inXML);
    void HandleConfigEnd(MushcoreXML& inXML);
    void HandleValueEnd(MushcoreXML& inXML);
    void NullHandler(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef std::map<string, void (GameConfig::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;
    // End of XML stuff
    
    void SaveToFile(void) const;

    static GameConfig *m_instance;
};
#endif
