#ifndef __LOCATION_H__
#define __LOCATION_H__

#include <string>

class Location
{
public:
    Location(std::string name, double latitude, double longtitud);
    std::string get_name() { return name; }

private:
    std::string name;
    double latitude;
    double longitude;
};

#endif