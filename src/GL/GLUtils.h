/*
 * $Id: GLUtils.h,v 1.1 2002/05/10 22:38:23 southa Exp $
 * $Log: GLUtils.h,v $
 * Revision 1.1  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 */

#include "GLStandard.h"

class GLUtils
{
public:
    static void OrthoPrologue(void);
    static void OrthoEpilogue(void);
    static void CheckGLError(void);
    static void StandardInit(void);
    static void GameInit(void);
private:
    static void SafetyHandler(void);
};
