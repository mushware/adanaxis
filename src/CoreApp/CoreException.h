#ifndef COREEXCEPTION_HP
#define COREEXCEPTION_HP
/*
 * $Id: CoreException.h,v 1.4 2002/05/27 12:58:42 southa Exp $
 * $Log: CoreException.h,v $
 * Revision 1.4  2002/05/27 12:58:42  southa
 * GameContract and global configs added
 *
 * Revision 1.3  2002/05/24 18:08:35  southa
 * CoreXML and game map
 *
 * Revision 1.2  2002/05/24 16:23:09  southa
 * Config and typenames
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.4  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.3  2002/05/08 17:26:35  southa
 * API tidying
 *
 * Revision 1.2  2002/03/05 22:44:45  southa
 * Changes to command handling
 *
 * Revision 1.1  2002/03/01 12:21:25  southa
 * Added first CoreScript code
 *
 */

class FileFail: public exception
{
public:
    FileFail(const string& inFilename, const string& inMessage):
    m_filename(inFilename), m_message(inMessage) {}
    ~FileFail() throw() {}
    const string& FilenameGet(void) const throw () {return m_filename;}
    const string& MessageGet(void) const throw() {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_filename;
    string m_message;
};

inline ostream& operator<<(ostream &s, FileFail f)
{
    return s << "File '" << f.FilenameGet() << "': " << f.MessageGet();
}

class ConfigFail: public exception
{
public:
    ConfigFail(const string &inMessage) {m_message=inMessage;}
    ~ConfigFail() throw() {}
    const string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_message;
};

inline ostream& operator<<(ostream &s, ConfigFail f)
{
    return s << f.StringGet();
}

class CommandFail: public exception
{
public:
    CommandFail(const string &inMessage) {m_message=inMessage;}
    ~CommandFail() throw() {}
    const string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_message;
};

inline ostream& operator<<(ostream &s, CommandFail f)
{
    return s << f.StringGet();
}

class TestFail: public exception
{
public:
    TestFail(const string &inMessage) {m_message=inMessage;}
    ~TestFail() throw() {}
    const string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_message;
};

inline ostream& operator<<(ostream &s, TestFail f)
{
    return s << f.StringGet();
}


class XMLFail: public exception
{
public:
    XMLFail(const string &inMessage) {m_message=inMessage;}
    ~XMLFail() throw() {}
    const string& SPrint(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_message;
};

inline ostream& operator<<(ostream &s, XMLFail f)
{
    return s<<f.SPrint();
}

class ExpressionFail: public exception
{
public:
    ExpressionFail(const string &inMessage) {m_message=inMessage;}
    ~ExpressionFail() throw() {}
    const string& SPrint(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_message;
};

inline ostream& operator<<(ostream &s, ExpressionFail f)
{
    return s<<f.SPrint();
}

class LoaderFail: public exception
{
public:
    LoaderFail(const string& inFilename, const string& inReason):
        m_filename(inFilename), m_reason(inReason)
        { m_message="File '"+m_filename+"': "+m_reason; }
    ~LoaderFail() throw() {}
    const string& FilenameGet(void) {return m_filename;}
    const string& ReasonGet(void) {return m_reason;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_filename;
    string m_reason;
    string m_message;
};

inline ostream& operator<<(ostream &s, LoaderFail f)
{
    return s << "File '" << f.FilenameGet() << "': " << f.ReasonGet();
}

#endif