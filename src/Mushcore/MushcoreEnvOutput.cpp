//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreEnvOutput.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } z82eyx/KmLVNe26o2qoozA
/*
 * $Id: MushcoreEnvOutput.cpp,v 1.4 2003/09/17 19:40:35 southa Exp $
 * $Log: MushcoreEnvOutput.cpp,v $
 * Revision 1.4  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:10  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/12 17:32:59  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.3  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.2  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/11/07 11:59:02  southa
 * Web commands
 *
 */

#include "MushcoreEnvOutput.h"

#include "MushcoreEnv.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MushcoreEnvOutput::MushcoreEnvOutput(MushcoreEnv& inEnv, ostream& inOut) :
    m_envRef(inEnv)
{
    m_envRef.OutSet(inOut);
}

MushcoreEnvOutput::~MushcoreEnvOutput()
{
    m_envRef.OutReset();
}
