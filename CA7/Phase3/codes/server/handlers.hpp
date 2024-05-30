#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "server.hpp"
#include "../backend/location.hpp"
#include "../backend/interface.hpp"
#include "../backend/exceptions.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class SignupHandler : public RequestHandler
{
public:
  SignupHandler(Interface *interface, std::string &error_massage);
  Response *callback(Request *);

private:
  Interface *interface;
  std::string &error_massage;
};

class TripHandler : public RequestHandler
{
public:
  TripHandler(Interface *interface, std::string &error_massage, double &trip_cost, int &trip_id);
  Response *callback(Request *);

private:
  Interface *interface;
  std::string &error_massage;
  double &trip_cost;
  int &trip_id;
};

class DeleteHandler : public RequestHandler
{
public:
  DeleteHandler(Interface *interface, std::string &error_massage);
  Response *callback(Request *);

private:
  Interface *interface;
  std::string &error_massage;
};

class AuthenticateHandler : public RequestHandler
{
public:
  AuthenticateHandler(Interface *interface, std::string &error_massage, std::string &driver_name);
  Response *callback(Request *);

private:
  Interface *interface;
  std::string &error_massage;
  std::string &driver_name;
};

class ShowTripHandler : public RequestHandler
{
public:
  ShowTripHandler(Interface *interface, std::string &error_massage);
  Response *callback(Request *);

private:
  Interface *interface;
  std::string &error_massage;
};

class AcceptHandler : public RequestHandler
{
public:
  AcceptHandler(Interface *interface, std::string &error_massage,std::string &driver_name);
  Response *callback(Request *);

private:
  Interface *interface;
  std::string &error_massage;
  std::string &driver_name;
};

class FinishHandler : public RequestHandler
{
public:
  FinishHandler(Interface *interface, std::string &error_massage,std::string &driver_name);
  Response *callback(Request *);

private:
  Interface *interface;
  std::string &error_massage;
  std::string &driver_name;
};

class ExceptHandler : public RequestHandler
{
public:
  ExceptHandler(std::string &error_massage);
  Response *callback(Request *);

private:
  std::string &error_massage;
};
class CostHandler : public RequestHandler
{
public:
  CostHandler(double &cost);
  Response *callback(Request *);

private:
  double &cost;
};

class SuccesReserve : public RequestHandler
{
public:
  SuccesReserve(int &trip_id);
  Response *callback(Request *);

private:
  int &trip_id;
};

int find_loc_index(std::string loc_name, std::vector<Location> locs);

#endif
