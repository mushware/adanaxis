#ifndef GAMEMAP_H
#define GAMEMAP_H
/*
 * $Id: GameMap.h,v 1.4 2002/05/28 13:05:55 southa Exp $
 * $Log: GameMap.h,v $
 * Revision 1.4  2002/05/28 13:05:55  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.3  2002/05/26 16:08:49  southa
 * CoreXML loader
 *
 * Revision 1.2  2002/05/25 17:16:15  southa
 * CoreXML implementation
 *
 * Revision 1.1  2002/05/24 18:08:35  southa
 * CoreXML and game map
 *
 */

#include "mushCore.h"

class GameMap : public CorePickle, private CoreXMLHandler
{
public:
    GameMap(): m_state(kInit) {}
    virtual void Pickle(ostream& inOut) const;
    virtual void Unpickle(CoreXML& inXML);
    U32 At(U32 inX, U32 inY) {COREASSERT(inX<m_xsize);COREASSERT(inY<m_ysize);return m_map[inY][inX];}
    U32 XSize(void) {return m_xsize;}
    U32 YSize(void) {return m_ysize;}
    
protected:
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

    void HandleDataEnd(CoreXML& inXML);
    void HandleGameMapStart(CoreXML& inXML);
    void HandleGameMapEnd(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);

    enum
    {
        kInit,
        kData,
        kNumStates
    };
    
private:
    typedef map<string, void (GameMap::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    U32 m_state;

    vector< vector<U32> > m_map;
    tSize m_xsize;
    tSize m_ysize;
};
#endif
