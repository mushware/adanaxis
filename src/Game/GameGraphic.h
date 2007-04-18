//%includeGuardStart {
#ifndef GAMEGRAPHIC_H
#define GAMEGRAPHIC_H
//%includeGuardStart } mSvX5xP5Zam4WQhfpheceQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameGraphic.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } vDvsfxIpA+iEssKZ6zx+xw
/*
 * $Id: GameGraphic.h,v 1.19 2006/06/01 15:38:58 southa Exp $
 * $Log: GameGraphic.h,v $
 * Revision 1.19  2006/06/01 15:38:58  southa
 * DrawArray verification and fixes
 *
 * Revision 1.18  2005/05/19 13:02:02  southa
 * Mac release work
 *
 * Revision 1.17  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.16  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.15  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.14  2003/08/21 23:08:46  southa
 * Fixed file headers
 *
 * Revision 1.13  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.12  2003/01/09 14:57:02  southa
 * Created Mushcore
 *
 * Revision 1.11  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.10  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/11/24 23:18:23  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.8  2002/10/22 20:42:04  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/12 11:22:21  southa
 * GraphicModel work
 *
 * Revision 1.6  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/04 20:27:37  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.1  2002/06/04 17:02:11  southa
 * More work
 *
 */

#include "mushMushcore.h"

class GameGraphic : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    GameGraphic() {}
    virtual ~GameGraphic() {}
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const = 0;
    virtual void Unpickle(MushcoreXML& inXML) = 0;
    virtual void Render(void) = 0;
    virtual char *TypeNameGet(void) const = 0;

    static GameGraphic& NewFromType(const std::string& inName);
    
protected:
    void UnpicklePrologue(void) {}
    void UnpickleEpilogue(void) {}
private:
};

inline std::ostream& operator<<(std::ostream &inOut, const GameGraphic& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
