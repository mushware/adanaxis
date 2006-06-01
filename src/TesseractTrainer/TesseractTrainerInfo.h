//%includeGuardStart {
#ifndef TESSERACTTRAINERINFO_H
#define TESSERACTTRAINERINFO_H
//%includeGuardStart } ufVSJcKPA53cgWOU6771bA
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerInfo.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 15ip5/2N9DZTzxzbJP8HHQ
/*
 * $Id: TesseractTrainerInfo.h,v 1.2 2005/05/19 13:02:22 southa Exp $
 * $Log: TesseractTrainerInfo.h,v $
 * Revision 1.2  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/03 15:47:00  southa
 * Quaternion work
 *
 */

#include "mushMushcore.h"

class TesseractTrainerInfo : public MushcoreInfo
{
public:
    virtual std::string ApplicationNameGet(void);
    virtual std::string PackageNameGet(void);
    virtual std::string PackageVersionGet(void);

    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
