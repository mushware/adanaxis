#ifndef GLLIGHTDEF_H
#define GLLIGHTDEF_H

/*
 * $Id: GLLightDef.h,v 1.3 2002/10/08 17:13:16 southa Exp $
 * $Log: GLLightDef.h,v $
 * Revision 1.3  2002/10/08 17:13:16  southa
 * Tiered maps
 *
 * Revision 1.2  2002/10/08 11:58:52  southa
 * Light cache
 *
 * Revision 1.1  2002/10/06 22:09:58  southa
 * Initial lighting test
 *
*/

#include "mushCore.h"
#include "GLStandard.h"
#include "GLPoint.h"
#include "GLVector.h"

class GLLightDef
{
public:
    GLLightDef() {} // For vector
    explicit GLLightDef(const GLVector& inPos) : pos(inPos) {}
    GLVector pos;
    void Pickle(ostream& inOut, const string& inPrefix="") const;
    void Unpickle(CoreXML& inXML);
};

#endif
