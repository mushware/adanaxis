/*
 * $Id: GameFloorMap.cpp,v 1.1 2002/05/30 16:21:53 southa Exp $
 * $Log: GameFloorMap.cpp,v $
 * Revision 1.1  2002/05/30 16:21:53  southa
 * Pickleable GameContract
 *
 * Revision 1.5  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.4  2002/05/28 13:05:55  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.3  2002/05/26 16:08:48  southa
 * CoreXML loader
 *
 * Revision 1.2  2002/05/25 17:16:15  southa
 * CoreXML implementation
 *
 * Revision 1.1  2002/05/24 18:08:35  southa
 * CoreXML and game map
 *
 */

#include "GameFloorMap.h"
#include "GameData.h"

CoreInstaller GameFloorMapInstaller(GameFloorMap::Install);

void
GameFloorMap::NullHandler(CoreXML& inXML)
{
}

void
GameFloorMap::HandleGameFloorMapStart(CoreXML& inXML)
{
    m_xsize=inXML.GetAttribOrThrow("xsize").U32Get();
    m_ysize=inXML.GetAttribOrThrow("ysize").U32Get();
    m_state=kData;
}

void
GameFloorMap::HandleGameFloorMapEnd(CoreXML& inXML)
{
    inXML.StopHandler();
}

void
GameFloorMap::HandleDataEnd(CoreXML& inXML)
{
    istringstream inStream(inXML.TopData());
    U32 data;
    vector<U32> vec;
    while (inStream >> data)
    {
        char isComma;
        vec.push_back(data);
        if ((inStream >> isComma) && (isComma == ','))
        {
            // Carry on - comma's there so expect more data
        }
        else
        {
            break;
        }
    }
    if (vec.size() != m_xsize)
    {
        cerr << "Warning: Data size does not match map size" << endl;
        vec.resize(m_xsize);
    }
    m_map.insert(m_map.begin(), vec);
}

void
GameFloorMap::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<gamemap xsize=\"" << m_xsize << "\" ysize=\"" << m_ysize << "\">" << endl;
    for (vector< vector<U32> >::const_reverse_iterator x_it = m_map.rbegin(); x_it != m_map.rend(); x_it++)
    {
        inOut << inPrefix << "  <data>";
        for (vector<U32>::const_iterator y_it = x_it->begin(); y_it != x_it->end(); y_it++)
        {
            inOut << *y_it;
            if (y_it+1 != x_it->end())
            {
                inOut << ",";
            }
        }
        inOut << "</data>" << endl;
    }
    inOut << inPrefix << "</gamemap>" << endl;
}

void
GameFloorMap::Unpickle(CoreXML& inXML)
{
    m_startTable.resize(kNumStates);
    m_endTable.resize(kNumStates);
    m_startTable[kInit]["gamemap"] = &GameFloorMap::HandleGameFloorMapStart;
    m_startTable[kData]["data"] = &GameFloorMap::NullHandler;
    m_endTable[kData]["gamemap"] = &GameFloorMap::HandleGameFloorMapEnd;
    m_endTable[kData]["data"] = &GameFloorMap::HandleDataEnd;

    m_map.clear();
    inXML.ParseStream(*this);
    if (m_map.size() != m_ysize)
    {
        cerr << "Warning: Data size does not match map size" << endl;
        m_map.resize(m_ysize);
    }
}

void
GameFloorMap::XMLStartHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_startTable[m_state].find(inXML.TopTag());

    if (p != m_startTable[m_state].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected tag <" << inXML.TopTag() << ">.  Potential matches are";
ElementFunctionMap::iterator p = m_startTable[m_state].begin();
        while (p != m_startTable[m_state].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
GameFloorMap::XMLEndHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_state].find(inXML.TopTag());

    if (p != m_endTable[m_state].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
        ostringstream message;
        message << "Unexpected end of tag </" << inXML.TopTag() << ">.  Potential matches are";
ElementFunctionMap::iterator p = m_endTable[m_state].begin();
        while (p != m_endTable[m_state].end())
        {
            message << " <" << p->first << ">";
            p++;
        }
        inXML.Throw(message.str());
    }
}

void
GameFloorMap::XMLDataHandler(CoreXML& inXML)
{
}

CoreScalar
GameFloorMap::LoadFloorMap(CoreCommand& ioCommand, CoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(CommandFail("Usage: loadfloormap <name> <filename>"));
    }
    string name, filename;
    ioCommand.PopParam(name);
    ioCommand.PopParam(filename);
    ifstream inStream(filename.c_str());
    if (!inStream) throw(LoaderFail(filename, "Could not open file"));
    CoreXML xml(inStream, filename);
    GameData::Instance().FloorMapGetOrCreate(name)->Unpickle(xml);
    return CoreScalar(0);
}

void
GameFloorMap::Install(void)
{
    CoreApp::Instance().AddHandler("loadfloormap", LoadFloorMap);
}

