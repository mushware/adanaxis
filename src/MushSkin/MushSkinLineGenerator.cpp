//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinLineGenerator.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /ogEinXWaS3ZU9x1JORYXA
/*
 * $Id$
 * $Log$
 */

#include "MushSkinLineGenerator.h"

using namespace Mushware;
using namespace std;

void
MushSkinLineGenerator::CellNoiseInitialise(Mushware::U32 inSeed)
{
	m_cellNoiseHash.resize(2*kHashSize);

	U32 seed = inSeed;
	for (U32 i=0; i<kHashSize; ++i)
	{
		U32 lo = 16807 * ((seed+1) & 0xffff);
		U32 hi = 16807 * (seed >> 16);
		lo += (hi & 0x7fff) << 16;
		lo += hi >> 15;
		if (lo > 0x7fffffff) lo -= 0x7fffffff;
		seed = lo;
		m_cellNoiseHash[i] = seed & 0xff;
		m_cellNoiseHash[i+kHashSize] = seed & 0xff;
	}
	MushcoreLog::Sgl().InfoLog() << "m_cellNoiseHash=" << m_cellNoiseHash << endl;
}

//%outOfLineFunctions {

const char *MushSkinLineGenerator::AutoName(void) const
{
    return "MushSkinLineGenerator";
}

MushcoreVirtualObject *MushSkinLineGenerator::AutoClone(void) const
{
    return new MushSkinLineGenerator(*this);
}

MushcoreVirtualObject *MushSkinLineGenerator::AutoCreate(void) const
{
    return new MushSkinLineGenerator;
}

MushcoreVirtualObject *MushSkinLineGenerator::AutoVirtualFactory(void)
{
    return new MushSkinLineGenerator;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinLineGenerator", MushSkinLineGenerator::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinLineGenerator::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "cellNoiseHash=" << m_cellNoiseHash;
    ioOut << "]";
}
bool
MushSkinLineGenerator::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "cellNoiseHash")
    {
        ioIn >> m_cellNoiseHash;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushSkinLineGenerator::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("cellNoiseHash");
    ioOut << m_cellNoiseHash;
}
//%outOfLineFunctions } 9v76OG1vOKDgtg1eBbFSEg
