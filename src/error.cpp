#include "error.h"

void errExit(int errNum, std::string errMsg)
{
    std::cerr << errMsg << std::endl;
    exit(errNum);
}
