/*
 * $Id: GameMap.h,v 1.1 2002/05/24 18:08:35 southa Exp $
 * $Log: GameMap.h,v $
 * Revision 1.1  2002/05/24 18:08:35  southa
 * CoreXML and game map
 *
 */

#include "mushCore.h"

class GameMap : public CorePickle, private CoreXML
{
public:

    virtual void Pickle(ostream& inOut) const;
    virtual void Unpickle(istream& inIn);

private:
    virtual void XMLStartElement(void);
    virtual void XMLEndElement(void);
    virtual void XMLCharacterData(void);
    
// private:
    vector< vector<U32> > m_map;
};
