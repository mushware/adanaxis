/*
 * $Id: GameMap.cpp,v 1.4 2002/05/28 13:05:55 southa Exp $
 * $Log: GameMap.cpp,v $
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

#include "GameMap.h"

void
GameMap::NullHandler(CoreXML& inXML)
{
}

void
GameMap::HandleGameMapStart(CoreXML& inXML)
{
    m_xsize=inXML.GetAttribOrThrow("xsize").U32Get();
    m_ysize=inXML.GetAttribOrThrow("ysize").U32Get();
    m_state=kData;
}

void
GameMap::HandleGameMapEnd(CoreXML& inXML)
{
    inXML.Stop();
}

void
GameMap::HandleDataEnd(CoreXML& inXML)
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
GameMap::Pickle(ostream& inOut) const
{
    inOut << "<gamemap xsize=\"" << m_xsize << "\" ysize=\"" << m_ysize << "\">" << endl;
    for (vector< vector<U32> >::const_reverse_iterator x_it = m_map.rbegin(); x_it != m_map.rend(); x_it++)
    {
        inOut << "<data>";
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
    inOut << "</gamemap>" << endl;
}

void
GameMap::Unpickle(CoreXML& inXML)
{
    m_startTable.resize(kNumStates);
    m_endTable.resize(kNumStates);
    m_startTable[kInit]["gamemap"] = &GameMap::HandleGameMapStart;
    m_startTable[kData]["data"] = &GameMap::NullHandler;
    m_endTable[kData]["gamemap"] = &GameMap::HandleGameMapEnd;
    m_endTable[kData]["data"] = &GameMap::HandleDataEnd;

    m_map.clear();
    inXML.ParseStream(*this);
    if (m_map.size() != m_ysize)
    {
        cerr << "Warning: Data size does not match map size" << endl;
        m_map.resize(m_ysize);
    }
}

void
GameMap::XMLStartHandler(CoreXML& inXML)
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
GameMap::XMLEndHandler(CoreXML& inXML)
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
GameMap::XMLDataHandler(CoreXML& inXML)
{
}
