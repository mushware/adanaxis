#ifndef MUSHCOREAUTOMONKEY_H
#define MUSHCOREAUTOMONKEY_H
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
 * $Id: MushcoreAutoMonkey.h,v 1.2 2003/01/11 13:03:16 southa Exp $
 * $Log: MushcoreAutoMonkey.h,v $
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:05  southa
 * Created Mushcore
 *
 * Revision 1.6  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
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
 * Name changed to MushcoreAutoMonkey
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
 * Added MushcoreAutoMonkey
 *
 */

#include "MushcoreStandard.h"

class MushcoreAutoMonkey
{
public:
    MushcoreAutoMonkey(): m_refCtrPtr(new int(1)) {}
    ~MushcoreAutoMonkey();
    MushcoreAutoMonkey(const MushcoreAutoMonkey& inMonkey);
    bool FreeInDestructor(void *inDataPtr) const; // Call in destructor, free shared area if returns true
    Mushware::S32 ReferenceCountGet(void) const {return *m_refCtrPtr;} // For testing
    MushcoreAutoMonkey& operator=(const MushcoreAutoMonkey&);
    
private:
    void Swap(MushcoreAutoMonkey& inMonkey);
    Mushware::S32 *m_refCtrPtr;
};
#endif
