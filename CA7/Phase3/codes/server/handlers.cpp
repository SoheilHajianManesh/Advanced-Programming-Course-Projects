#include "handlers.hpp"

using namespace std;

SignupHandler::SignupHandler(Interface *interface, string &error_massage) : interface(interface), error_massage(error_massage) {}

Response *SignupHandler::callback(Request *req)
{
  try
  {
    string username = req->getBodyParam("username");
    string role = req->getBodyParam("role");
    interface->signup(username, role);
    Response *res = Response::redirect("/success");
    return res;
  }
  catch (Import_except &except)
  {
    error_massage = except.get_massage();
    Response *res = Response::redirect("/error");
    return res;
  }
}
TripHandler::TripHandler(Interface *interface, string &error_massage, double &trip_cost, int &trip_id) : interface(interface), error_massage(error_massage),
                                                                                                         trip_cost(trip_cost), trip_id(trip_id)
{
}
Response *TripHandler::callback(Request *req)
{
  try
  {
    string username = req->getBodyParam("username");
    string origin = req->getBodyParam("origin");
    int origin_index = find_loc_index(origin, interface->locs);
    string destination = req->getBodyParam("destination");
    int destination_index = find_loc_index(destination, interface->locs);
    bool in_hurry;
    if (req->getBodyParam("in_hurry") == "yes")
      in_hurry = true;
    else
      in_hurry = false;
    string action = req->getBodyParam("action");
    if (action == "submit")
    {
      interface->add_new_trip(username, origin_index, destination_index, in_hurry);
      trip_id++;
      Response *res = Response::redirect("/succesres");
      return res;
    }
    else if (action == "price")
    {
      trip_cost = interface->get_cost(username, origin_index, destination_index, in_hurry);
      Response *res = Response::redirect("/cost");
      return res;
    }
  }
  catch (Import_except &except)
  {
    error_massage = except.get_massage();
    Response *res = Response::redirect("/error");
    return res;
  }
}

DeleteHandler::DeleteHandler(Interface *interface, string &error_massage) : interface(interface), error_massage(error_massage) {}

Response *DeleteHandler::callback(Request *req)
{
  try
  {
    string username = req->getBodyParam("username");
    string trip_id = req->getBodyParam("id");
    interface->delete_a_trip(username, stoi(trip_id));
    Response *res = Response::redirect("/success");
    return res;
  }
  catch (Import_except &except)
  {
    error_massage = except.get_massage();
    Response *res = Response::redirect("/error");
    return res;
  }
}

AuthenticateHandler::AuthenticateHandler(Interface *interface, string &error_massage, string &driver_name) : interface(interface), error_massage(error_massage), driver_name(driver_name) {}

Response *AuthenticateHandler::callback(Request *req)
{
  try
  {
    string username = req->getBodyParam("username");
    interface->show_trips(username);
    driver_name = username;
    Response *res = Response::redirect("/show");
    return res;
  }
  catch (Import_except &except)
  {
    error_massage = except.get_massage();
    Response *res = Response::redirect("/error");
    return res;
  }
}

ShowTripHandler::ShowTripHandler(Interface *interface, string &error_massage) : interface(interface), error_massage(error_massage) {}

Response *ShowTripHandler::callback(Request *req)
{
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
        << "<!DOCTYPE html>" << endl
        << "<html>" << endl
      //  << "   <head><title style=\"text-align:center;\">TRIPS</title></head>" << endl
        << "   <head><style> table, th, td { border: 1px solid; font-size:30px; color:white;} table.center {margin-left: auto; margin-right: auto;}body {background-color: rgb(80,80,80);}    a{color:black;text-decoration: none;text-align:center;font-size: 30px;}</style></head>"<<endl
        << "      <body style=\"text-align: center;\">" << endl
        << "         <table class=\"center\">"<<endl
        << "              <tr>" << endl
        << "                  <th>ID</th>" << endl
        << "                  <th>Origin</th>" << endl
        << "                  <th>Destination</th>" << endl
        << "                  <th>Status</th>" << endl
        << "                  <th>Price</th>" << endl
        << "                  <th>&nbsp;</th>" << endl
        << "                  <th>&nbsp;</th>" << endl
        << "              </tr>" << endl;
    for (int i = 0; i < interface->trips.size(); i++)
    {
      if(interface->trips[i].get_status()==DELETE)
          continue;
      body
          << "            <tr>" << endl
          << "                 <td>" << interface->trips[i].get_id() << "</td>" << endl
          << "                 <td>" << interface->trips[i].get_origin() << "</td>" << endl
          << "                 <td>" << interface->trips[i].get_destination() << "</td>" << endl
          << "                 <td>" << interface->trips[i].get_status_str() << "</td>" << endl
          << "                 <td>" << to_string(interface->trips[i].get_price()) << "</td>" << endl
          << "                 <td><a href='finish?id=" << interface->trips[i].get_id() << "'>Finish Trip</a></td>" << endl
          << "                 <td><a href='accept?id=" << interface->trips[i].get_id() << "'>Accept Trip</a></td>" << endl
          << "             </tr>" << endl;
    }
    body
        << "         </table>" << endl
        << "    <a href=\"/\">Home Page</style></a>" << endl
        << "    </body>" << endl
        << "</html>" << endl;
    res->setBody(body.str());
    return res;  
}

AcceptHandler::AcceptHandler(Interface *interface, string &error_massage, string &driver_name) : interface(interface), error_massage(error_massage), driver_name(driver_name) {}

Response *AcceptHandler::callback(Request *req)
{
  try
  {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    int id = stoi(req->getQueryParam("id"));
    interface->accept_a_trip_by_driver(driver_name, id);
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<body style=\"text-align: center;\">";
    body += "<style>h1{background-color: rgb(37, 40, 15);color:  White ;} body {background-color: rgb(0, 0, 0);}    a{color:burlywood;text-decoration: none;text-align:center;font-size: 40px;}   </style>;";
    body += "<h1>";
    body += "TRIP WAS ACCEPTED SUCCESFULLY BY YOU";
    body += "</h1>";
    body += "<a href=\"/\">   Home Page                  </style></a>";
    body += "<a href=\"/show\">  Trips Page   </style></a>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
  }
  catch (Import_except &except)
  {
    error_massage = except.get_massage();
    Response *res = Response::redirect("/error");
    return res;
  }
}

FinishHandler::FinishHandler(Interface *interface, string &error_massage, string &driver_name) : interface(interface), error_massage(error_massage), driver_name(driver_name) {}

Response *FinishHandler::callback(Request *req)
{
  try
  {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    int id = stoi(req->getQueryParam("id"));
    interface->finish_a_trip(driver_name,id);
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<body style=\"text-align: center;\">";
    body += "<style>h1{background-color: rgb(37, 40, 15);color:  White ;} body {background-color: rgb(0, 0, 0);}    a{color:burlywood;text-decoration: none;text-align:center;font-size: 40px;}  </style>;";
    body += "<h1>";
    body += "TRIP WAS FINISHED SUCCESFULLY BY YOU";
    body += "</h1>";
    body += "<a href=\"/\">       Home Page                  </style></a>";
    body += "<a href=\"/show\">   Trips Page   </style></a>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
  }
  catch (Import_except &except)
  {
    error_massage = except.get_massage();
    Response *res = Response::redirect("/error");
    return res;
  }
}

ExceptHandler::ExceptHandler(std::string &error_massage) : error_massage(error_massage) {}

Response *ExceptHandler::callback(Request *req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<style>h1{background-color: rgb(37, 40, 15);color:  White ;} body {background-color: rgb(0, 0, 0);}  a{color:burlywood;text-decoration: none;text-align:center;font-size: 40px;}     </style>;";
  body += "<h1>";
  body += error_massage;
  body += "</h1>";
  body += "<a href=\"/\">Home Page</style></a>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}
CostHandler::CostHandler(double &cost) : cost(cost) {}

Response *CostHandler::callback(Request *req)
{
  string trip_cost = to_string(cost);
  for (int i = 0; i < 4; i++)
    trip_cost.pop_back();
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<style>h1{background-color: rgb(37, 40, 15);color:  White ;} body {background-color: rgb(0, 0, 0);} a{color:burlywood;text-decoration: none;text-align:center;font-size: 40px;} </style>;";
  body += "<h1>";
  body += "YOUR TRIP COST:";
  body += trip_cost;
  body += "</h1>";
  body += "<a href=\"/reserve\">Back</style></a>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

SuccesReserve::SuccesReserve(int &trip_id) : trip_id(trip_id) {}

Response *SuccesReserve::callback(Request *req)
{
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<style>h1{background-color: rgb(37, 40, 15);color:  White ;} body {background-color: rgb(0, 0, 0);} a{color:burlywood;text-decoration: none;text-align:center;font-size: 40px;}      </style>;";
  body += "<h1>";
  body += "YOUR TRIP ID:";
  body += to_string(trip_id);
  body += "</h1>";
  body += "<a href=\"/\">Home Page</style></a>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

int find_loc_index(string loc_name, vector<Location> locs)
{
  for (int i = 0; i < locs.size(); i++)
    if (locs[i].get_name() == loc_name)
      return i;
  throw Import_except(NOT_EXIST_MASSAGE);
}