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
 * $Id: MushcoreEnvOutput.cpp,v 1.2 2003/01/12 17:32:59 southa Exp $
 * $Log: MushcoreEnvOutput.cpp,v $
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
