/*
 * $Id: GLLightDef.h,v 1.1 2002/10/06 22:09:58 southa Exp $
 * $Log: GLLightDef.h,v $
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
};
