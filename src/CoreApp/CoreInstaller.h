/*
 * $Id: CoreInstaller.h,v 1.1 2002/03/07 22:24:33 southa Exp $
 * $Log: CoreInstaller.h,v $
 * Revision 1.1  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */
 
class CoreInstaller
{
public:
    CoreInstaller(void (*fn)()) {fn();}
};
