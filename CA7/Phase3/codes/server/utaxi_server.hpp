#ifndef __UTAXI_SERVER_H__
#define __UTAXI_SERVER_H__
#include "server.hpp"
#include "handlers.hpp"
#include "../backend/location.hpp"
#include "../backend/const.hpp"
#include "../backend/exceptions.hpp"
#include "../backend/interface.hpp"
#include <iostream>
#include <vector>
#include <fstream>

class Handle_system
{
public:
    Handle_system(Interface *inteface);
    void handle_input();

private:
    Interface *interface;
    std::string error_massage;
    double trip_cost;
    int trip_id;
    std::string driver_name;
};
std::vector<Location> read_locs(std::string file_name);
std::vector<std::string> split(std::string line);
#endif