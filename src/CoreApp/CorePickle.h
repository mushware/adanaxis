/*
 * $Id$
 * $Log$
 */

#include "CoreStandard.h"

class CorePickle
{
public:
    virtual ~CorePickle() {}
    virtual void Pickle(istream& inOut) const = 0;
    virtual void Unpickle(ostream& inIn) = 0;
};
