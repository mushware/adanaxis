//%includeGuardStart {
#ifndef GAMECONFIGDEF_H
#define GAMECONFIGDEF_H
//%includeGuardStart } V9filyh3XsvK3mcDr1Ey9Q
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameConfigDef.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } VBKMYOvqeTbyD7gciu0RTQ
/*
 * $Id: GameConfigDef.h,v 1.12 2004/01/06 20:46:49 southa Exp $
 * $Log: GameConfigDef.h,v $
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
