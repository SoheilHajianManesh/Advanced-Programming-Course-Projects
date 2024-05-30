#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>

class Import_except
{
public:
    Import_except(std::string error_massage);

    std::string get_massage() { return error_massage; }

private:
    std::string error_massage;
};

#endif