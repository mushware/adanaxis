/*
 * $Id$
 * $Log$
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
        
    static auto_ptr<MediaNetLog> m_instance;
};

inline MediaNetLog&
MediaNetLog::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MediaNetLog);
    return *m_instance;
}
