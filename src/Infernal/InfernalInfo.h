//%includeGuardStart {
#ifndef INFERNALINFO_H
#define INFERNALINFO_H
//%includeGuardStart } KLp60caVtEHto70ibRNtpA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/InfernalInfo.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } hiixk1c31tPCzwMmFzo7dg
/*
 * $Id: InfernalInfo.h,v 1.4 2003/09/17 19:40:32 southa Exp $
 * $Log: InfernalInfo.h,v $
 * Revision 1.4  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:08:47  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/04/06 12:35:23  southa
 * Fixes for release
 *
 * Revision 1.1  2003/03/11 22:15:09  southa
 * Added InfernalInfo
 *
 */

#include "Mushcore.h"

class InfernalInfo : public MushcoreInfo
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
