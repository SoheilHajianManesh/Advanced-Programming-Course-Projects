#include "inputhandler.hpp"
using namespace std;

vector<string> split(string line)
{
    vector<string> info;
    string parse;
    for (int i = 0, j = 0; i < line.size(); i++, j++)
    {
        if (line[i] == SPACE || line[i] == SEPARATOR)
        {
            j = 0;
            info.push_back(parse);
            parse.clear();
            continue;
        }
        if (i == line.size() - 1)
        {
            parse.push_back(line[i]);
            info.push_back(parse);
            parse.clear();
        }
        parse.push_back(line[i]);
    }
    return info;
}
vector<Location> read_locs(string file_name)
{
    vector<Location> locs;
    ifstream my_file(file_name);
    string line;
    getline(my_file, line);
    while (getline(my_file, line))
    {
        vector<string> loc_infos = split(line);
        Location new_loc(loc_infos[0], stod(loc_infos[1]), stod(loc_infos[2]), stoi(loc_infos[3]));
        locs.push_back(new_loc);
    }
    return locs;
}
Handle_system::Handle_system(Interface *interface) : interface(interface)
{
}
void Handle_system::handle_input()
{
    while (getline(cin, command))
    {
        try
        {
            command_argument = split(command);
            if (command_argument[0] == "POST")
                post_commands();
            else if (command_argument[0] == "GET")
                get_commands();
            else if (command_argument[0] == "DELETE")
                delete_command();
            else
                throw Import_except(WRONG_DEMAND_MASSAGE);
        }
        catch (Import_except &except)
        {
            cout << except.get_massage();
        }
        command_argument.clear();
    }
}
int Handle_system::find_loc_index(string loc_name)
{
    for (int i = 0; i < interface->locs.size(); i++)
        if (interface->locs[i].get_name() == loc_name)
            return i;
    throw Import_except(NOT_EXIST_MASSAGE);
}
void Handle_system::post_commands()
{
    if (command_argument.size() < 5 || command_argument[2] != "?")
        throw Import_except(WRONG_DEMAND_MASSAGE);
    else if (command_argument[1] == "trips" && command_argument.size() != 11)
        throw Import_except(WRONG_DEMAND_MASSAGE);
    for (int i = 3; i < command_argument.size(); i++)
    {
        if (command_argument[i] == "username")
            username = command_argument[i + 1];
        if (command_argument[i] == "id")
            id = stoi(command_argument[i + 1]);
        if (command_argument[i] == "role")
            role = command_argument[i + 1];
        if (command_argument[i] == "origin")
            origin_index = find_loc_index(command_argument[i + 1]);
        if (command_argument[i] == "destination")
            destination_index = find_loc_index(command_argument[i + 1]);
        if (command_argument[i] == "in_hurry")
            if (command_argument[i + 1] == "yes")
                in_hurry = true;
            else
                in_hurry = false;
    }
    if (command_argument[1] == "signup")
        interface->signup(username, role);
    else if (command_argument[1] == "trips")
        interface->add_new_trip(username, origin_index, destination_index, in_hurry);
    else if (command_argument[1] == "accept")
        interface->accept_a_trip_by_driver(username, id);
    else if (command_argument[1] == "finish")
        interface->finish_a_trip(username, id);
    else
        throw Import_except(NOT_EXIST_MASSAGE);
}
void Handle_system::delete_command()
{
    if (command_argument[1] != "trips" || command_argument[2] != "?" || command_argument.size() != 7)
        throw Import_except(WRONG_DEMAND_MASSAGE);
    for (int i = 3; i < command_argument.size(); i++)
    {
        if (command_argument[i] == "username")
            username = command_argument[i + 1];
        if (command_argument[i] == "id")
            id = stoi(command_argument[i + 1]);
    }
    interface->delete_a_trip(username, id);
}
void Handle_system::get_commands()
{
    int check_which_command = 0;
    if (command_argument[2] != "?" || command_argument.size() < 7)
        throw Import_except(WRONG_DEMAND_MASSAGE);
    if (command_argument[1] == "trips" && command_argument.size() != 7)
        throw Import_except(WRONG_DEMAND_MASSAGE);
    if (command_argument[1] == "cost" && command_argument.size() != 11)
        throw Import_except(WRONG_DEMAND_MASSAGE);
    for (int i = 3; i < command_argument.size(); i++)
    {
        if (command_argument[i] == "username")
            username = command_argument[i + 1];
        if (command_argument[i] == "id")
        {
            id = stoi(command_argument[i + 1]);
            check_which_command++;
        }
        if (command_argument[i] == "sort_by_cost")
        {
            if (command_argument[i + 1] == "yes")
                sort_by_cost = true;
            else
                sort_by_cost = false;
            check_which_command--;
        }
        if (command_argument[i] == "origin")
            origin_index = find_loc_index(command_argument[i + 1]);
        if (command_argument[i] == "destination")
            destination_index = find_loc_index(command_argument[i + 1]);
        if (command_argument[i] == "in_hurry")
            if (command_argument[i + 1] == "yes")
                in_hurry = true;
            else
                in_hurry = false;
    }
    if (command_argument[1] == "trips" && check_which_command == 1)
        interface->show_requested_trip_info(username, id);
    else if (command_argument[1] == "trips" && check_which_command == -1)
        interface->show_trips(username, sort_by_cost);
    else if (command_argument[1] == "cost")
        interface->get_cost(username, origin_index, destination_index, in_hurry);
    else
        throw Import_except(NOT_EXIST_MASSAGE);
}