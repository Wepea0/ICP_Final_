//
// Created by Cyril K on 11/20/2022.
//

#ifndef C___INDIVIDUAL_PROJECT_ROUTE_H
#define C___INDIVIDUAL_PROJECT_ROUTE_H

#include <string>
#include <unordered_map>
#include <deque>
#include <queue>
#include <set>
#include "Airport.h"
using namespace std;

class Route {
private:
    string airlineIata, airlineId, sourceIata, sourceId, destIata, destId, codeshare, equipment, stops;

public:
    static unordered_map<string,vector<Route>> routes;
    static unordered_map<string,vector<Route>> flights;
    static unordered_map<string,string> parents;

    Route(string airlineIata,
          string airlineId,
          string sourceIata,
          string sourceId,
          string destIata,
          string destId,
          string stops);
    string getAirlineIata();
    string getAirlineId();
    string getSourceIata();
    string getSourceId();
    string getdestIata();
    string getdestId();
    string getNumStops();
    static bool contains(deque<string> q, string value);
    static bool set_contains(set<string> s, string value);
    static vector<string> solutionPath(string destinationIata);
    static void getFlights(string csvFile);
    static void findRoute(string csvFile);
    static vector<string> search(Airport start, Airport destination);
    static double haversine(Airport start, Airport destination);
    static void writeToFile(string start, string destination, vector<string> path, vector<string> flightPath, double distance);

};


#endif //C___INDIVIDUAL_PROJECT_ROUTE_H
