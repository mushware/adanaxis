/*
 * $Id$
 * $Log$
 */

#include "GLLightDef.h"

void
GLLightDef::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<light>" << pos << "</light>" << endl;
}

void
GLLightDef::Unpickle(CoreXML& inXML)
{
    pos.Unpickle(inXML);
}
