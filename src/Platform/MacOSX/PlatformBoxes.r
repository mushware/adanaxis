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
 * $Id: PlatformBoxes.r,v 1.2 2002/11/01 18:46:26 southa Exp $
 * $Log: PlatformBoxes.r,v $
 * Revision 1.2  2002/11/01 18:46:26  southa
 * UDP Links
 *
 * Revision 1.1  2002/10/15 18:16:41  southa
 * Mac error box
 *
 */


#include <Carbon/Carbon.r>
#include "PlatformBoxes.h"

resource 'DITL' (kPlatformFatalErrorBox) {
{       /* array DITLarray: 3 elements */
    /* [1] */
{20, 81, 42, 408},
    StaticText {
        disabled,
        "Infernal Contractor II"
    },
    /* [1] */
{56, 21, 122, 408},
    StaticText {
        disabled,
        "^0"
    },

    /* [3] */
{130, 342, 150, 408},
    Button {
        enabled,
        "Quit"
    }
}
};

resource 'ALRT' (kPlatformFatalErrorBox) {
{40, 40, 204, 480},
    200,
{       /* array: 4 elements */
    /* [1] */
    OK, visible, sound1,
    /* [2] */
    OK, visible, sound1,
    /* [3] */
    OK, visible, sound1,
    /* [4] */
    OK, visible, sound1
},
    alertPositionMainScreen
};

resource 'DITL' (kPlatformMinorErrorBox) {
{       /* array DITLarray: 3 elements */
    /* [1] */
{20, 81, 42, 408},
    StaticText {
        disabled,
        "Infernal Contractor II"
    },
    /* [1] */
{56, 21, 122, 408},
    StaticText {
        disabled,
        "^0"
    },

    /* [3] */
{130, 342, 150, 408},
    Button {
        enabled,
        "OK"
    }
}
};

resource 'ALRT' (kPlatformMinorErrorBox) {
{40, 40, 204, 480},
    200,
{       /* array: 4 elements */
    /* [1] */
    OK, visible, sound1,
    /* [2] */
    OK, visible, sound1,
    /* [3] */
    OK, visible, sound1,
    /* [4] */
    OK, visible, sound1
},
alertPositionMainScreen
};


resource 'DITL' (kPlatformQuestionBox) {
{       /* array DITLarray: 3 elements */
    /* [1] */
{20, 81, 42, 408},
    StaticText {
        disabled,
        "Infernal Contractor II"
    },
    /* [1] */
{56, 21, 122, 408},
    StaticText {
        disabled,
        "^0"
    }
}
};

resource 'ALRT' (kPlatformQuestionBox) {
{40, 40, 204, 480},
    200,
{       /* array: 4 elements */
    /* [1] */
    OK, visible, sound1,
    /* [2] */
    OK, visible, sound1,
    /* [3] */
    OK, visible, sound1,
    /* [4] */
    OK, visible, sound1
},
alertPositionMainScreen
};

