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
 * $Id: CoreAutoMonkey.cpp,v 1.3 2002/08/07 13:36:44 southa Exp $
 * $Log: CoreAutoMonkey.cpp,v $
 * Revision 1.3  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.2  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 09:12:53  southa
 * Name changed to CoreAutoMonkey
 *
 * Revision 1.7  2002/06/27 12:36:01  southa
 * Build process fixes
 *
 * Revision 1.6  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.5  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.4  2002/03/07 22:24:32  southa
 * Command interpreter working
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

#include "CoreAutoMonkey.h"
#include "CoreStandard.h"
#include "CoreSwitches.h"

CoreAutoMonkey::~CoreAutoMonkey()
{
    --*m_refCtrPtr;
    IFMONKEYTESTING(cerr << "Automonkey destroyed, refcount to " << ReferenceCountGet() << endl);
    if (*m_refCtrPtr == 0)
    {
        delete m_refCtrPtr;
        m_refCtrPtr=NULL;
        IFMONKEYTESTING(cerr << "CoreAutoMonkey workspace freed" << endl); 
    }
}

CoreAutoMonkey::CoreAutoMonkey(const CoreAutoMonkey& inMonkey)
{
    m_refCtrPtr=inMonkey.m_refCtrPtr;
    ++*m_refCtrPtr;
    IFMONKEYTESTING(cerr << "Automonkey copied, refcount to " << ReferenceCountGet() << endl);
}

void
CoreAutoMonkey::Swap(CoreAutoMonkey& inMonkey)
{
    int *temp=m_refCtrPtr;
    m_refCtrPtr=inMonkey.m_refCtrPtr;
    inMonkey.m_refCtrPtr=temp;
}

CoreAutoMonkey&
CoreAutoMonkey::operator=(const CoreAutoMonkey& inMonkey)
{
    CoreAutoMonkey temp(inMonkey);
    Swap(temp);
    return *this;
}

bool
CoreAutoMonkey::FreeInDestructor(void *inDataPtr) const
{
    if (*m_refCtrPtr < 1) throw("CoreAutoMonkey fault");
    IFMONKEYTESTING(cerr << "Automonkey InDestructorFree, refcount is " << ReferenceCountGet() << endl);
    return (*m_refCtrPtr == 1  && inDataPtr != NULL);
}

