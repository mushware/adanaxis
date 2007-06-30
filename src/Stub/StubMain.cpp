
#include <iostream>

int
main(int inArgC, char **inArgV)
{
    std::cout << "Stub application" << std::endl;
    for (unsigned int i=0; i<inArgC; ++i)
    {
        std::cout << "Arg " << i << " = '" << inArgV[i] << "'" << std::endl;
    }
}
