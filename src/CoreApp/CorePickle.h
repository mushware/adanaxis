/*
 * $Id: CorePickle.h,v 1.1 2002/05/24 16:23:10 southa Exp $
 * $Log: CorePickle.h,v $
 * Revision 1.1  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 */

#include "CoreStandard.h"

class CorePickle
{
public:
    virtual ~CorePickle() {}
    virtual void Pickle(ostream& inOut) const = 0;
    virtual void Unpickle(istream& inIn) = 0;
};
