/*
 *  PlatformMiscUtils.h
 *  core-app
 *
 *  Created by Southa on Tue Jun 11 2002.
 *  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
 *
 */

#include "mushCore.h"

class PlatformMiscUtils
{
public:
    static string GetApplPath(int argc, char *argv[]);
    static string GetSystemPath(int argc, char *argv[]);
    static void TweakArgs(string& ioString);
};
