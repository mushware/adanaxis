/*
 * $Id$
 * $Log$
 */

#include "Mustl.h"

// Blanket exception to cover all non-fatal network failures
class NetworkFail : public MustlFail
{
public:
    NetworkFail(const string& inMessage);
};

inline
NetworkFail::NetworkFail(const string& inMessage) :
    MustlFail(inMessage)
{}



