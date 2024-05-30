#ifndef __LOCATION_H__
#define __LOCATION_H__

#include <string>

class Location
{
public:
    Location(std::string name, double latitude, double longtitud, int traffic);
    std::string get_name() { return name; }
    double get_latitude() { return latitude; }
    double get_longtitude() { return longitude; }
    int get_traffic() { return traffic; }

private:
    std::string name;
    double latitude;
    double longitude;
    int traffic;
};

#endif