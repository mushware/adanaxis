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
 * $Id: AutoMonkey.cpp,v 1.6 2002/05/10 16:39:38 southa Exp $
 * $Log: AutoMonkey.cpp,v $
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
 * Added AutoMonkey
 *
 */

#include "AutoMonkey.h"
#include "CoreStandard.h"
#include "CoreSwitches.h"

AutoMonkey::~AutoMonkey()
{
    --*m_refCtrPtr;
    IFMONKEYTESTING(cerr << "Automonkey destroyed, refcount to " << ReferenceCountGet() << endl);
    if (*m_refCtrPtr == 0)
    {
        delete m_refCtrPtr;
        m_refCtrPtr=NULL;
        IFMONKEYTESTING(cerr << "AutoMonkey workspace freed" << endl); 
    }
}

AutoMonkey::AutoMonkey(const AutoMonkey& inMonkey)
{
    m_refCtrPtr=inMonkey.m_refCtrPtr;
    ++*m_refCtrPtr;
    IFMONKEYTESTING(cerr << "Automonkey copied, refcount to " << ReferenceCountGet() << endl);
}

void
AutoMonkey::Swap(AutoMonkey& inMonkey)
{
    int *temp=m_refCtrPtr;
    m_refCtrPtr=inMonkey.m_refCtrPtr;
    inMonkey.m_refCtrPtr=temp;
}

AutoMonkey&
AutoMonkey::operator=(const AutoMonkey& inMonkey)
{
    AutoMonkey temp(inMonkey);
    Swap(temp);
    return *this;
}

bool
AutoMonkey::FreeInDestructor(void *inDataPtr) const
{
    if (*m_refCtrPtr < 1) throw("AutoMonkey fault");
    IFMONKEYTESTING(cerr << "Automonkey InDestructorFree, refcount is " << ReferenceCountGet() << endl);
    return (*m_refCtrPtr == 1  && inDataPtr != NULL);
}

