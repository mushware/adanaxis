/*
 * $Id$
 * $Log$
 */

#include <iosfwd>
#include <stdexcept>
#include <string>

class MustlFail: public exception
{
public:
    MustlFail(const string &inMessage) {m_message=inMessage;}
    ~MustlFail() throw();
    const char *what() const throw() { return m_message.c_str(); }

    const string& Print(void) const { return m_message; }

private:
    string m_message;
};

ostream& operator<<(ostream &ioOut, MustlFail f);
