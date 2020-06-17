//%includeGuardStart {
#ifndef GAMECONFIGDEF_H
#define GAMECONFIGDEF_H
//%includeGuardStart } V9filyh3XsvK3mcDr1Ey9Q
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameConfigDef.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 4UJDsZFUMwCQu9/SPwZxwg
/*
 * $Id: GameConfigDef.h,v 1.14 2006/06/01 15:38:56 southa Exp $
 * $Log: GameConfigDef.h,v $
 * Revision 1.14  2006/06/01 15:38:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.13  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.12  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.11  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.10  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:08:36  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/11 13:03:12  southa
 * Use Mushcore header
 *
 * Revision 1.7  2003/01/09 14:57:00  southa
 * Created Mushcore
 *
 * Revision 1.6  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.5  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/11/25 18:02:56  southa
 * Mushware ID work
 *
 * Revision 1.3  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.2  2002/11/14 19:35:31  southa
 * Configuration work
 *
 * Revision 1.1  2002/11/14 17:29:08  southa
 * Config database
 *
 */

#include "mushMushcore.h"

class GameConfigDef
{
public:
    virtual ~GameConfigDef();
    virtual const MushcoreScalar ValueGet(void) const = 0;
    virtual void ValueSet(const MushcoreScalar& inValue) = 0;
    virtual bool FromPostRetrieve(const std::string& inName, const std::string& inData) = 0;
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName) = 0;

protected:
    static void SelectPrologue(std::ostream& ioOut, const std::string& inName);
    static void SelectOption(std::ostream& ioOut, const std::string& inName, const std::string& inValue, bool inSelected);
    static void SelectOption(std::ostream& ioOut, const std::string& inName, Mushware::U32 inValue, bool inSelected);
    static void SelectEpilogue(std::ostream& ioOut);
};

class GameConfigDefU32 : public GameConfigDef
{
public:
    GameConfigDefU32(Mushware::U32 inValue, Mushware::U32 inLowLimit, Mushware::U32 inHighLimit);
    
    virtual ~GameConfigDefU32();
    virtual const MushcoreScalar ValueGet(void) const;
    virtual void ValueSet(const MushcoreScalar& inValue );
    virtual bool FromPostRetrieve(const std::string& inName, const std::string& inData);
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName);

private:
    Mushware::U32 m_value;
    Mushware::U32 m_lowLimit;
    Mushware::U32 m_highLimit;
};

class GameConfigDefString : public GameConfigDef
{
public:
    GameConfigDefString(const std::string& inValue, const std::string& inMenu="");

    virtual ~GameConfigDefString();
    virtual const MushcoreScalar ValueGet(void) const;
    virtual void ValueSet(const MushcoreScalar& inValue);
    virtual bool FromPostRetrieve(const std::string& inName, const std::string& inData);
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName);

private:
    std::string m_value;
    std::string m_menu;
};

class GameConfigDefPassword : public GameConfigDef
{
public:
    GameConfigDefPassword(const std::string& inValue);
    virtual ~GameConfigDefPassword();
    virtual const MushcoreScalar ValueGet(void) const;
    virtual void ValueSet(const MushcoreScalar& inValue);
    virtual bool FromPostRetrieve(const std::string& inName, const std::string& inData);
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName);

private:
    std::string m_value;
};

class GameConfigDefBool : public GameConfigDef
{
public:
    explicit GameConfigDefBool(bool inValue);

    virtual ~GameConfigDefBool();
    virtual const MushcoreScalar ValueGet(void) const;
    virtual void ValueSet(const MushcoreScalar& inValue);
    virtual bool FromPostRetrieve(const std::string& inName, const std::string& inData);
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName);

private:
    bool m_value;
};


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
