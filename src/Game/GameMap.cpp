/*
 * $Id: GameMap.cpp,v 1.1 2002/05/24 18:08:35 southa Exp $
 * $Log: GameMap.cpp,v $
 * Revision 1.1  2002/05/24 18:08:35  southa
 * CoreXML and game map
 *
 */

#include "GameMap.h"

void
GameMap::Pickle(ostream& inOut) const
{
}

void
GameMap::Unpickle(istream& inIn)
{
    XMLParseStream(inIn);
}

void
GameMap::XMLStartElement(void)
{
}

void
GameMap::XMLEndElement(void)
{
    XMLDumpTops(cerr);
}

void
GameMap::XMLCharacterData(void)
{
}
