//%includeGuardStart {
#ifndef MUSHCOREENVOUTPUT_H
#define MUSHCOREENVOUTPUT_H
//%includeGuardStart } dRAH2I/ElRq00sHm6ljVrg
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreEnvOutput.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } +L5wsU1ar+K7bI2otmpMCg
/*
 * $Id: MushcoreEnvOutput.h,v 1.4 2003/09/17 19:40:35 southa Exp $
 * $Log: MushcoreEnvOutput.h,v $
 * Revision 1.4  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:11  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.2  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/11/07 11:59:02  southa
 * Web commands
 *
 */

#include "MushcoreStandard.h"

class MushcoreEnv;

class MushcoreEnvOutput
{
public:
    MushcoreEnvOutput(MushcoreEnv& inEnv, std::ostream& inOut);
    ~MushcoreEnvOutput();

private:
    MushcoreEnv& m_envRef;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
