#ifndef GLKEYS_H
#define GLKEYS_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GLKeys.h,v 1.1 2002/05/31 15:18:16 southa Exp $
 * $Log: GLKeys.h,v $
 * Revision 1.1  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 */

#include "mushCore.h"

class GLKeys
{
public:
    enum tKeyValue
    {
        // Special keys start at 0x100
        kKeyF1=0x100,
        kKeyF2,
        kKeyF3,
        kKeyF4,
        kKeyF5,
        kKeyF6,
        kKeyF7,
        kKeyF8,
        kKeyF9,
        kKeyF10,
        kKeyF11,
        kKeyF12,
        kKeyLeft,
        kKeyUp,
        kKeyRight,
        kKeyDown,
        kKeyPageUp,
        kKeyPageDown,
        kKeyHome,
        kKeyEnd,
        kKeyInsert,
        kNumberOfKeys
    };
    GLKeys(U32 inKeyValue): m_keyValue(static_cast<tKeyValue>(inKeyValue)) {}
    GLKeys(tKeyValue inKeyValue): m_keyValue(inKeyValue) {}
    U32 ValueGet(void) const {return m_keyValue;}
    
private:
    tKeyValue m_keyValue;
};
#endif
