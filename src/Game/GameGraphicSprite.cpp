/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: GameGraphicSprite.cpp,v 1.3 2002/06/27 12:36:07 southa Exp $
 * $Log: GameGraphicSprite.cpp,v $
 * Revision 1.3  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/04 20:27:37  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.1  2002/06/04 17:02:11  southa
 * More work
 *
 */

#include "GameGraphicSprite.h"

void
GameGraphicSprite::Render(void)
{
    if (m_texRef.Exists())
    {
        GLUtils::DrawSprite(*m_texRef.TextureGet());
    }    
}

void
GameGraphicSprite::HandleNameEnd(CoreXML& inXML)
{
    m_texRef.NameSet(inXML.TopData());
}

void
GameGraphicSprite::HandleGraphicEnd(CoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameGraphicSprite::NullHandler(CoreXML& inXML)
{
}

void
GameGraphicSprite::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<name>" << m_texRef.NameGet() << "</name>" << endl;
}

void
GameGraphicSprite::UnpicklePrologue(void)
{
    GameGraphic::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["name"] = &GameGraphicSprite::NullHandler;
    m_endTable[kPickleData]["name"] = &GameGraphicSprite::HandleNameEnd;
    m_endTable[kPickleData]["graphic"] = &GameGraphicSprite::HandleGraphicEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
}

void
GameGraphicSprite::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameGraphicSprite::UnpickleEpilogue(void)
{
    GameGraphic::UnpickleEpilogue();
    m_startTable.resize(0);
    m_endTable.resize(0);
}

void
GameGraphicSprite::XMLStartHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
//        if (m_pickleState == kPickleData)
//        {
//            GameGraphic::XMLStartHandler(inXML);
//            m_pickleState=kPickleWithinBase;
//            ++m_baseThreaded;
//        }
//        else
        {
            ostringstream message;
            message << "Unexpected tag <" << inXML.TopTag() << "> in GraphicSprite.  Potential matches are";
ElementFunctionMap::iterator p = m_startTable[m_pickleState].begin();
            while (p != m_startTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GameGraphicSprite::XMLEndHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
//        if (m_pickleState == kPickleWithinBase)
//        {
//          GameGraphic::XMLEndHandler(inXML);
//            --m_baseThreaded;
//            if (m_baseThreaded == 0)
//            {
//                m_pickleState=kPickleData;
//            }
//        }
//        else
        {
            ostringstream message;
            message << "Unexpected end of tag </" << inXML.TopTag() << "> in GraphicSprite.  Potential matches are";
ElementFunctionMap::iterator p = m_endTable[m_pickleState].begin();
            while (p != m_endTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GameGraphicSprite::XMLDataHandler(CoreXML& inXML)
{
}
