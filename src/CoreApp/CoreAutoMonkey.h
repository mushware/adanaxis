#ifndef COREAUTOMONKEY_H
#define COREAUTOMONKEY_H
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
 * $Id: CoreAutoMonkey.h,v 1.1 2002/07/02 09:12:53 southa Exp $
 * $Log: CoreAutoMonkey.h,v $
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
