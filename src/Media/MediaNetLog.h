/*
 * $Id: MediaNetLog.h,v 1.1 2002/11/04 15:50:32 southa Exp $
 * $Log: MediaNetLog.h,v $
 * Revision 1.1  2002/11/04 15:50:32  southa
 * Network log
 *
 */

#include "mushCore.h"



class MediaNetLog
{
public:
    ~MediaNetLog();

    ostream& Log(void);
    void OpenFile(const string& inName);
    void CloseFile(void);
    
    static MediaNetLog& Instance(void);
    
protected:
    MediaNetLog();

private:
    ofstream *m_outStream;
        
    static MediaNetLog *m_instance;
};

inline MediaNetLog&
MediaNetLog::Instance(void)
{
    if (m_instance != NULL) return *m_instance;
    m_instance=new MediaNetLog;
    return *m_instance;
}
