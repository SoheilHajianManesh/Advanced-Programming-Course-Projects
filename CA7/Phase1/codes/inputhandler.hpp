#ifndef __READINPUT_H__
#define __READINPUT_H__
#include "location.hpp"
#include "const.hpp"
#include "exceptions.hpp"
#include "interface.hpp"
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
    void post_commands();
    void get_commands();
    void delete_command();
    int find_loc_index(std::string loc_name);
    std::string command;
    std::vector<std::string> command_argument;
    std::string username;
    std::string role;
    int id;
    int origin_index;
    int destination_index;
};
std::vector<Location> read_locs(std::string file_name);
std::vector<std::string> split(std::string line);
#endif