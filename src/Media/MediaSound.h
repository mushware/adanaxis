/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class MediaSound
{
public:
    MediaSound() { cerr << "MediaSound constructed" << endl; }
    ~MediaSound() { cerr << "MediaSound destructor" << endl; }
        
private:
    string m_name;
};

