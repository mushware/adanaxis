#ifndef MUSTLFAIL_H
#define MUSTLFAIL_H
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
 * $Id: MustlFail.h,v 1.1 2002/12/12 18:38:24 southa Exp $
 * $Log: MustlFail.h,v $
 * Revision 1.1  2002/12/12 18:38:24  southa
 * Mustl separation
 *
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

ostream& operator<<(std::ostream &ioOut, MustlFail f);
#endif
