/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameMap : public CorePickle
{
public:
    
    virtual void Pickle(istream& inOut) const;
    virtual void Unpickle(ostream& inIn);

private:
    vector< vector<U32> > m_map;
};
