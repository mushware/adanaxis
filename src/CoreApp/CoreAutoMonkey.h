#ifndef COREAUTOMONKEY_H
#define COREAUTOMONKEY_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: CoreAutoMonkey.h,v 1.5 2002/10/22 20:41:57 southa Exp $
 * $Log: CoreAutoMonkey.h,v $
 * Revision 1.5  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.2  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 09:12:53  southa
 * Name changed to CoreAutoMonkey
 *
 * Revision 1.2  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 * Revision 1.2  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.1  2002/02/23 11:43:34  southa
 * Added CoreAutoMonkey
 *
 */

class CoreAutoMonkey
{
public:
    CoreAutoMonkey(): m_refCtrPtr(new int(1)) {}
    ~CoreAutoMonkey();
    CoreAutoMonkey(const CoreAutoMonkey& inMonkey);
    bool FreeInDestructor(void *inDataPtr) const; // Call in destructor, free shared area if returns true
    int ReferenceCountGet(void) const {return *m_refCtrPtr;} // For testing
    CoreAutoMonkey& operator=(const CoreAutoMonkey&);
    
private:
    void Swap(CoreAutoMonkey& inMonkey);
    int *m_refCtrPtr;
};
#endif
