#ifndef GLKEYS_H
#define GLKEYS_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GLKeys.h,v 1.9 2003/01/11 13:03:11 southa Exp $
 * $Log: GLKeys.h,v $
 * Revision 1.9  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.8  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.3  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 * Revision 1.2  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/31 15:18:16  southa
 * Keyboard reading
 *
 */

#include "Mushcore.h"

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
        kKeyMouse1,
        kKeyMouse2,
        kKeyMouse3,
        kKeyMouse4,
        kKeyMouse5,    
        kNumberOfKeys
    };
    GLKeys(Mushware::U32 inKeyValue): m_keyValue(static_cast<tKeyValue>(inKeyValue)) {}
    GLKeys(tKeyValue inKeyValue): m_keyValue(inKeyValue) {}
    Mushware::U32 ValueGet(void) const {return m_keyValue;}
    
private:
    tKeyValue m_keyValue;
};
#endif
