/*
 * $Id: GameConfigDef.h,v 1.3 2002/11/22 11:42:06 southa Exp $
 * $Log: GameConfigDef.h,v $
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

#include "mushCore.h"

class GameConfigDef
{
public:
    virtual ~GameConfigDef();
    virtual const CoreScalar ValueGet(void) const = 0;
    virtual void ValueSet(const CoreScalar& inValue) = 0;
    virtual bool FromPostRetrieve(const string& inName, const string& inData) = 0;
    virtual void WebInputPrint(ostream& ioOut, const string& inName) = 0;

protected:
    static void SelectPrologue(ostream& ioOut, const string& inName);
    static void SelectOption(ostream& ioOut, const string& inName, const string& inValue, bool inSelected);
    static void SelectOption(ostream& ioOut, const string& inName, U32 inValue, bool inSelected);
    static void SelectEpilogue(ostream& ioOut);
};

class GameConfigDefU32 : public GameConfigDef
{
public:
    GameConfigDefU32(U32 inValue, U32 inLowLimit, U32 inHighLimit);
    
    virtual ~GameConfigDefU32();
    virtual const CoreScalar ValueGet(void) const;
    virtual void ValueSet(const CoreScalar& inValue );
    virtual bool FromPostRetrieve(const string& inName, const string& inData);
    virtual void WebInputPrint(ostream& ioOut, const string& inName);

private:
    U32 m_value;
    U32 m_lowLimit;
    U32 m_highLimit;
};

class GameConfigDefString : public GameConfigDef
{
public:
    GameConfigDefString(const string& inValue, const string& inMenu="");

    virtual ~GameConfigDefString();
    virtual const CoreScalar ValueGet(void) const;
    virtual void ValueSet(const CoreScalar& inValue);
    virtual bool FromPostRetrieve(const string& inName, const string& inData);
    virtual void WebInputPrint(ostream& ioOut, const string& inName);

private:
    string m_value;
    string m_menu;
};

class GameConfigDefPassword : public GameConfigDef
{
public:
    GameConfigDefPassword(const string& inValue);
    virtual ~GameConfigDefPassword();
    virtual const CoreScalar ValueGet(void) const;
    virtual void ValueSet(const CoreScalar& inValue);
    virtual bool FromPostRetrieve(const string& inName, const string& inData);
    virtual void WebInputPrint(ostream& ioOut, const string& inName);

private:
    string m_value;
};

class GameConfigDefBool : public GameConfigDef
{
public:
    explicit GameConfigDefBool(bool inValue);

    virtual ~GameConfigDefBool();
    virtual const CoreScalar ValueGet(void) const;
    virtual void ValueSet(const CoreScalar& inValue);
    virtual bool FromPostRetrieve(const string& inName, const string& inData);
    virtual void WebInputPrint(ostream& ioOut, const string& inName);

private:
    bool m_value;
};


