#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "driver.hpp"
#include "passenger.hpp"
#include "person.hpp"
#include "trip.hpp"
#include "location.hpp"
#include "exceptions.hpp"
#include <vector>
#include <algorithm>
#include <stdio.h>

class Interface
{
public:
    Interface(std::vector<Location> locs);
    void signup(std::string name, std::string role);
    void add_new_trip(std::string passenger, int origin_index, int destination_index, bool in_hurry);
    void get_cost(std::string passenger, int origin_index, int destination_index, bool in_hurry);
    void show_trips(std::string name, bool sort_by_cost);
    void show_requested_trip_info(std::string name, int id);
    void delete_a_trip(std::string passenger, int trip_id);
    void accept_a_trip_by_driver(std::string driver_name, int trip_id);
    void finish_a_trip(std::string driver_name, int trip_id);
    std::vector<Location> locs;

private:
    void sort_trips_by_id();
    void sort_trips_by_cost();
    void check_member_exist(std::string username);
    void check_duplicate_name(std::string name);
    int find_trip_index(int id);
    int find_member_index(std::string name);
    int find_location_index(std::string loc_name);
    std::vector<Trip> trips;
    std::vector<Person *> members;
};
#endif