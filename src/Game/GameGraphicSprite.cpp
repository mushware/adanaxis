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
 * $Id: GameGraphicSprite.cpp,v 1.18 2003/01/13 14:31:58 southa Exp $
 * $Log: GameGraphicSprite.cpp,v $
 * Revision 1.18  2003/01/13 14:31:58  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.17  2003/01/09 14:57:02  southa
 * Created Mushcore
 *
 * Revision 1.16  2003/01/07 17:13:42  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.15  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.14  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.13  2002/11/24 23:18:23  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.12  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.11  2002/10/12 15:25:18  southa
 * Facet renderer
 *
 * Revision 1.10  2002/10/08 21:44:10  southa
 * 3D maps
 *
 * Revision 1.9  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.7  2002/07/23 14:10:46  southa
 * Added GameMotion
 *
 * Revision 1.6  2002/07/19 15:44:41  southa
 * Graphic optimisations
 *
 * Revision 1.5  2002/07/08 14:22:02  southa
 * Rotated desks
 *
 * Revision 1.4  2002/07/06 18:04:19  southa
 * More designer work
 *
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

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

void
GameGraphicSprite::Render(void)
{
    if (m_texRef.Exists())
    {
        GLUtils::PushMatrix();
        if (m_rotation != 0)
        {
            GLUtils::RotateAboutZ(m_rotation);
        }
        GLUtils::Translate(m_offset);
        if (m_texRef.TextureGet()->NeedsAlpha())
        {
            GLState::BlendSet(GLState::kBlendTransparent);
        }
        else
        {
            GLState::BlendSet(GLState::kBlendSolid);
        }
        GLUtils::DrawSprite(*m_texRef.TextureGet(), m_rectangle);
        GLUtils::PopMatrix();
    }    
}

void
GameGraphicSprite::HandleNameEnd(MushcoreXML& inXML)
{
    m_texRef.NameSet(inXML.TopData());
}

void
GameGraphicSprite::HandleRectEnd(MushcoreXML& inXML)
{
    m_rectangle.Unpickle(inXML);
}

void
GameGraphicSprite::HandleOffsetEnd(MushcoreXML& inXML)
{
    m_offset.Unpickle(inXML);
}

void
GameGraphicSprite::HandleRotateEnd(MushcoreXML& inXML)
{
    istringstream data(inXML.TopData());
    if (!(data >> m_rotation)) inXML.Throw("Bad format for rotate.  Should be <rotate>90</rotate>");
}

void
GameGraphicSprite::HandleGraphicEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameGraphicSprite::NullHandler(MushcoreXML& inXML)
{
}

void
GameGraphicSprite::Pickle(ostream& inOut, const string& inPrefix) const
{
    inOut << inPrefix << "<name>" << m_texRef.NameGet() << "</name>" << endl;
    m_rectangle.Pickle(inOut, inPrefix);
    m_offset.Pickle(inOut, inPrefix);
    inOut << inPrefix << "<rotate>" << m_rotation << "</rotate>" << endl;
}

void
GameGraphicSprite::UnpicklePrologue(void)
{
    GameGraphic::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["name"] = &GameGraphicSprite::NullHandler;
    m_endTable[kPickleData]["name"] = &GameGraphicSprite::HandleNameEnd;
    m_startTable[kPickleData]["rect"] = &GameGraphicSprite::NullHandler;
    m_endTable[kPickleData]["rect"] = &GameGraphicSprite::HandleRectEnd;
    m_startTable[kPickleData]["offset"] = &GameGraphicSprite::NullHandler;
    m_endTable[kPickleData]["offset"] = &GameGraphicSprite::HandleOffsetEnd;
    m_startTable[kPickleData]["rotate"] = &GameGraphicSprite::NullHandler;
    m_endTable[kPickleData]["rotate"] = &GameGraphicSprite::HandleRotateEnd;
    m_endTable[kPickleData]["graphic"] = &GameGraphicSprite::HandleGraphicEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    m_rotation=0;
    m_rectangle=GLRectangle(0,0,1,1);
    m_offset=GLVector(0,0,0);
}

void
GameGraphicSprite::Unpickle(MushcoreXML& inXML)
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
GameGraphicSprite::XMLStartHandler(MushcoreXML& inXML)
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
GameGraphicSprite::XMLEndHandler(MushcoreXML& inXML)
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
GameGraphicSprite::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
GameGraphicSprite::TypeNameGet(void) const
{
    return "gamegraphicsprite";
}
