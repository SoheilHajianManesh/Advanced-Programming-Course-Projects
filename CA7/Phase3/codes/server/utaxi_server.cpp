#include "utaxi_server.hpp"
using namespace std;

Handle_system::Handle_system(Interface *interface) : interface(interface)
{
    trip_id = 0;
}
void Handle_system::handle_input()
{
    try
    {
        Server server(5050);
        server.get("/signup", new ShowPage("static/signupcss.html"));
        server.post("/signup", new SignupHandler(interface, error_massage));
        server.get("/success", new ShowPage("static/succescss.html"));
        server.get("/reserve", new ShowPage("static/tripcss.html"));
        server.post("/reserve", new TripHandler(interface, error_massage, trip_cost, trip_id));
        server.get("/del", new ShowPage("static/deletecss.html"));
        server.post("/del", new DeleteHandler(interface, error_massage));
        server.get("/search", new ShowPage("static/Authenticationcss.html"));
        server.post("/search", new AuthenticateHandler(interface, error_massage, driver_name));
        server.get("/show", new ShowTripHandler(interface, error_massage));
        server.get("/accept", new AcceptHandler(interface, error_massage, driver_name));
        server.get("/finish", new FinishHandler(interface, error_massage, driver_name));
        server.get("/error", new ExceptHandler(error_massage));
        server.get("/cost", new CostHandler(trip_cost));
        server.get("/succesres", new SuccesReserve(trip_id));
        server.get("/utaxi.png", new ShowImage("pics/utaxi.png"));
        server.get("/", new ShowPage("static/homecss.html"));
        server.run();
    }
    catch (Import_except &except)
    {
        cerr << except.get_massage() << endl;
    }
}





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