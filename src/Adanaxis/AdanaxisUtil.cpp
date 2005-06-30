//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisUtil.cpp
 *
 * Copyright: Andy Southgate 2005
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
//%Header } CFEozIhAxC4/w3MDbuOShQ
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisUtil.h"

#include "AdanaxisVolatileData.h"

using namespace Mushware;
using namespace std;

void
AdanaxisUtil::TestPiecesCreate(AdanaxisLogic& ioLogic)
{
    AdanaxisVolatileData::tDecoList& decoListRef = ioLogic.VolatileData().DecoListWRef();
    decoListRef.push_back(AdanaxisPieceDeco("testObj1"));
    AdanaxisVolatileData::tDeco& decoRef = decoListRef.back();
    
    decoRef.PostWRef().PosSet(t4Val(0,0,0,-10));
    MushMesh4Library::Sgl().UnitTesseractCreate(decoRef.MeshWRef());
}

