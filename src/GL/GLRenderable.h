#ifndef GL_RENDERABLE_H
#define GL_RENDERABLE_H
/*
 * $Id$
 * $Log$
 */

class GLRenderable
{
public:
    virtual ~GLRenderable() {}
    virtual void Render(void) const = 0;
    virtual GLRenderable *Clone(void) const = 0;
    
};
#endif
