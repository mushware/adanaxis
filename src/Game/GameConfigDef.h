/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameConfigDef
{
public:
    virtual ~GameConfigDef();
    virtual const CoreScalar ValueGet(void) const = 0;
    virtual void ValueSet(const CoreScalar& inValue) = 0;
    virtual bool FromPostRetrieve(const string& inName, const string& inData) = 0;
};

class GameConfigDefU32 : public GameConfigDef
{
public:
    GameConfigDefU32(U32 inValue, U32 inLowLimit, U32 inHighLimit);
    
    virtual ~GameConfigDefU32();
    virtual const CoreScalar ValueGet(void) const;
    virtual void ValueSet(const CoreScalar& inValue );
    virtual bool FromPostRetrieve(const string& inName, const string& inData);

private:
    U32 m_value;
    U32 m_lowLimit;
    U32 m_highLimit;
};

class GameConfigDefString : public GameConfigDef
{
public:
    GameConfigDefString(const string& inValue);

    virtual ~GameConfigDefString();
    virtual const CoreScalar ValueGet(void) const;
    virtual void ValueSet(const CoreScalar& inValue);
    virtual bool FromPostRetrieve(const string& inName, const string& inData);

private:
    string m_value;
};



