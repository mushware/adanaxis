#ifndef MUSHCOREEXCEPTION_H
#define MUSHCOREEXCEPTION_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MushcoreException.h,v 1.1 2003/01/09 14:57:06 southa Exp $
 * $Log: MushcoreException.h,v $
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.23  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.22  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.21  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.20  2002/12/13 01:07:25  southa
 * Mustl work
 *
 * Revision 1.19  2002/11/14 17:29:07  southa
 * Config database
 *
 * Revision 1.18  2002/10/31 16:41:32  southa
 * Network client
 *
 * Revision 1.17  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.16  2002/10/12 11:22:20  southa
 * GraphicModel work
 *
 * Revision 1.15  2002/10/08 11:58:52  southa
 * Light cache
 *
 * Revision 1.14  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.13  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.12  2002/07/06 18:04:15  southa
 * More designer work
 *
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
 * MushcoreXML and game map
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
 * Added first MushcoreScript code
 *
 */

#include "MushcoreStandard.h"

class FileFail: public std::exception
{
public:
    FileFail(const std::string& inFilename, const std::string& inMessage):
    m_filename(inFilename), m_message(inMessage) {}
    ~FileFail() throw() {}
    const std::string& FilenameGet(void) const throw () {return m_filename;}
    const std::string& MessageGet(void) const throw() {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_filename;
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, FileFail f)
{
    return s << "File '" << f.FilenameGet() << "': " << f.MessageGet();
}

class LogicFail: public std::exception
{
public:
    LogicFail(const std::string &inMessage) {m_message=inMessage;}
    ~LogicFail() throw() {}
    const std::string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, LogicFail f)
{
    return s << f.StringGet();
}

class ConfigFail: public std::exception
{
public:
    ConfigFail(const std::string &inMessage) {m_message=inMessage;}
    ~ConfigFail() throw() {}
    const std::string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, ConfigFail f)
{
    return s << f.StringGet();
}

class ReferenceFail: public std::exception
{
public:
    ReferenceFail(const std::string &inMessage) {m_message=inMessage;}
    ~ReferenceFail() throw() {}
    const std::string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, ReferenceFail f)
{
    return s << f.StringGet();
}

class FatalFail: public std::exception
{
public:
    FatalFail(const std::string &inMessage) {m_message=inMessage;}
    ~FatalFail() throw() {}
    const std::string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, FatalFail f)
{
    return s << f.StringGet();
}

class VerifyFail: public std::exception
{
public:
    VerifyFail(const std::string &inMessage) {m_message=inMessage;}
    ~VerifyFail() throw() {}
    const std::string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, VerifyFail f)
{
    return s << f.StringGet();
}

class CommandFail: public std::exception
{
public:
    CommandFail(const std::string &inMessage) {m_message=inMessage;}
    ~CommandFail() throw() {}
    const std::string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, CommandFail f)
{
    return s << f.StringGet();
}

class TestFail: public std::exception
{
public:
    TestFail(const std::string &inMessage) {m_message=inMessage;}
    ~TestFail() throw() {}
    const std::string& StringGet(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, TestFail f)
{
    return s << f.StringGet();
}


class XMLFail: public std::exception
{
public:
    XMLFail(const std::string &inMessage) {m_message=inMessage;}
    ~XMLFail() throw() {}
    const std::string& SPrint(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, XMLFail f)
{
    return s<<f.SPrint();
}

class ExpressionFail: public std::exception
{
public:
    ExpressionFail(const std::string &inMessage) {m_message=inMessage;}
    ~ExpressionFail() throw() {}
    const std::string& SPrint(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, ExpressionFail f)
{
    return s<<f.SPrint();
}

class LoaderFail: public std::exception
{
public:
    LoaderFail(const std::string& inFilename, const std::string& inReason):
        m_filename(inFilename), m_reason(inReason)
        { m_message="File '"+m_filename+"': "+m_reason; }
    ~LoaderFail() throw() {}
    const std::string& FilenameGet(void) {return m_filename;}
    const std::string& ReasonGet(void) {return m_reason;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_filename;
    std::string m_reason;
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, LoaderFail f)
{
    return s << "File '" << f.FilenameGet() << "': " << f.ReasonGet();
}

class DeviceFail: public std::exception
{
public:
    DeviceFail(const std::string &inMessage) {m_message=inMessage;}
    ~DeviceFail() throw() {}
    const std::string& SPrint(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, DeviceFail f)
{
    return s<<f.SPrint();
}

class ResourceFail: public std::exception
{
public:
    ResourceFail(const std::string &inMessage) {m_message=inMessage;}
    ~ResourceFail() throw() {}
    const std::string& SPrint(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, ResourceFail f)
{
    return s<<f.SPrint();
}

class SpecifierFail: public std::exception
{
public:
    SpecifierFail(const std::string &inMessage) {m_message=inMessage;}
    ~SpecifierFail() throw() {}
    const std::string& SPrint(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, SpecifierFail f)
{
    return s<<f.SPrint();
}

class SyntaxFail: public std::exception
{
public:
    SyntaxFail(const std::string &inMessage) {m_message=inMessage;}
    ~SyntaxFail() throw() {}
    const std::string& SPrint(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, SyntaxFail f)
{
    return s<<f.SPrint();
}

class ValueFail: public std::exception
{
public:
    ValueFail(const std::string &inMessage) {m_message=inMessage;}
    ~ValueFail() throw() {}
    const std::string& SPrint(void) {return m_message;}
    const char* what() const throw() {return m_message.c_str();}

private:
    std::string m_message;
};

inline std::ostream& operator<<(std::ostream &s, ValueFail f)
{
    return s<<f.SPrint();
}

#endif