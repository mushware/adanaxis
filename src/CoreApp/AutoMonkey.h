/*
 * $Id: AutoMonkey.h,v 1.3 2002/02/26 17:01:40 southa Exp $
 * $Log: AutoMonkey.h,v $
 * Revision 1.3  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 * Revision 1.2  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.1  2002/02/23 11:43:34  southa
 * Added AutoMonkey
 *
 */

class AutoMonkey
{
public:
    AutoMonkey(): m_refCtrPtr(new int(1)) {}
    ~AutoMonkey();
    AutoMonkey(const AutoMonkey& inMonkey);
    bool FreeInDestructor(void *inDataPtr) const; // Call in destructor, free shared area if returns true
    int ReferenceCountGet(void) const {return *m_refCtrPtr;} // For testing
    AutoMonkey& operator=(const AutoMonkey&);
    
private:
    void Swap(AutoMonkey& inMonkey);
    int *m_refCtrPtr;
};
