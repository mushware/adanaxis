/*
 * $Id: MediaNetLog.h,v 1.2 2002/11/07 00:53:37 southa Exp $
 * $Log: MediaNetLog.h,v $
 * Revision 1.2  2002/11/07 00:53:37  southa
 * localweb work
 *
 * Revision 1.1  2002/11/04 15:50:32  southa
 * Network log
 *
 */

#include "mushCore.h"

class MediaNetLog
{
public:
    MediaNetLog();
    ~MediaNetLog();

    ostream& Log(void);
    void OpenFile(const string& inName);
    void CloseFile(void);
    
    static MediaNetLog& Instance(void);
    
protected:

private:
    ofstream *m_outStream;

};
