#ifndef GLKEYS_H
#define GLKEYS_H
/*
 * $Id$
 * $Log$
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
