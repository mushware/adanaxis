/*
 * $Id: CorePickle.h,v 1.2 2002/05/25 17:17:18 southa Exp $
 * $Log: CorePickle.h,v $
 * Revision 1.2  2002/05/25 17:17:18  southa
 * CoreXML implementation
 *
 * Revision 1.1  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 */

#include "CoreStandard.h"

class CoreXML;

class CorePickle
{
public:
    virtual ~CorePickle() {}
    virtual void Pickle(ostream& inOut) const = 0;
    virtual void Unpickle(CoreXML& inXML) = 0;
    void Unpickle(const string& inFilename);
};
