#ifndef COREEXCEPTION_H
#define COREEXCEPTION_H
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
 * $Id: CoreException.h,v 1.11 2002/06/27 12:36:03 southa Exp $
 * $Log: CoreException.h,v $
 * Revision 1.11  2002/06/27 12:36:03  southa
 * Build process fixes
 *
 * Revision 1.10  2002/06/20 11:06:14  southa
 * Updated for cygwin
 *
 * Revision 1.9  2002/06/10 15:16:59  southa
 * Integration of MP3 player
 *
 * Revision 1.8  2002/06/05 12:28:05  southa
 * Map rendered using traits
 *
 * Revision 1.7  2002/06/04 14:11:21  southa
 * Traits loader first stage
 *
 * Revision 1.6  2002/05/28 16:37:36  southa
 * Texture references and decomposer
 *
 * Revision 1.5  2002/05/28 13:07:03  southa
 * Command parser extensions and TIFF loader
 *
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

class LogicFail: public exception
{
public:
    LogicFail(const string &inMessage) {m_message=inMessage;}
    ~LogicFail() throw() {}
    const string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_message;
};

inline ostream& operator<<(ostream &s, LogicFail f)
{
    return s << f.StringGet();
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

class ReferenceFail: public exception
{
public:
    ReferenceFail(const string &inMessage) {m_message=inMessage;}
    ~ReferenceFail() throw() {}
    const string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_message;
};

inline ostream& operator<<(ostream &s, ReferenceFail f)
{
    return s << f.StringGet();
}

class FatalFail: public exception
{
public:
    FatalFail(const string &inMessage) {m_message=inMessage;}
    ~FatalFail() throw() {}
    const string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_message;
};

inline ostream& operator<<(ostream &s, FatalFail f)
{
    return s << f.StringGet();
}

class VerifyFail: public exception
{
public:
    VerifyFail(const string &inMessage) {m_message=inMessage;}
    ~VerifyFail() throw() {}
    const string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_message;
};

inline ostream& operator<<(ostream &s, VerifyFail f)
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

class DeviceFail: public exception
{
public:
    DeviceFail(const string &inMessage) {m_message=inMessage;}
    ~DeviceFail() throw() {}
    const string& SPrint(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    string m_message;
};

inline ostream& operator<<(ostream &s, DeviceFail f)
{
    return s<<f.SPrint();
}


#endif
