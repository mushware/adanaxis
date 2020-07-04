//%includeGuardStart {
#ifndef GAMECONFIG_H
#define GAMECONFIG_H
//%includeGuardStart } +i4UrePC1RE8Qw2h1XH3Ww
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameConfig.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 2bY/7gTATcTg8TufwZRfnw
/*
 * $Id: GameConfig.h,v 1.21 2006/06/01 15:38:56 southa Exp $
 * $Log: GameConfig.h,v $
 * Revision 1.21  2006/06/01 15:38:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.20  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.19  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.18  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.17  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.16  2003/08/21 23:08:35  southa
 * Fixed file headers
 *
 * Revision 1.15  2003/02/05 17:06:35  southa
 * Build fixes
 *
 * Revision 1.14  2003/01/20 10:45:25  southa
 * Singleton tidying
 *
 * Revision 1.13  2003/01/11 13:03:12  southa
 * Use Mushcore header
 *
 * Revision 1.12  2003/01/09 14:57:00  southa
 * Created Mushcore
 *
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

#include "mushMushcore.h"

class GameConfig : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    static GameConfig& Sgl(void) { return *((m_instance==NULL)?m_instance=new GameConfig:m_instance); }
    
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

    typedef std::map<std::string, void (GameConfig::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;
    // End of XML stuff
    
    void SaveToFile(void) const;

    static GameConfig *m_instance;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
