/*
 * $Id$
 * $Log$
 */

#include "GraphWrangler.hp"
#include "GL/GLTexture.hp"

void
GraphWrangler::Process(bool &outDoQuit, bool &outRedraw)
{
    switch (m_state)
    {
        case kInit:
            Init();
            m_state=kFindVertAxis;
            break;

        case kFindVertAxis:
            FindVertAxis();
            m_state=kFindHorizAxis;
            outRedraw=true;
            break;

        case kFindHorizAxis:
            FindHorizAxis();
            outRedraw=true;
            break;
    }	
}

void
GraphWrangler::Init(void)
{
    m_width=m_tex.Width();
    m_height=m_tex.Height();
    m_hbytes=4*m_width; // fixme
    m_dataPtr=static_cast<U32 *>(m_tex.DataPtr());
}

void
GraphWrangler::FindVertAxis(void)
{
    *m_dataPtr=0xffffffff;
}

void
GraphWrangler::FindHorizAxis(void)
{
    m_dataPtr[2]=0x008000ff;
}
