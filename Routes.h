//
// Created by Wepea Buntugu on 23/11/2022.
//

#ifndef SENAXWEPEAFINALCPROJECT_ROUTES_H
#define SENAXWEPEAFINALCPROJECT_ROUTES_H

#include <string>
#include <unordered_map>
#include "Airports.h"
#include <deque>
#include <queue>
#include <set>

/**
 * <h2>Route class definitions</h2>
 */
using namespace std;

class Route {
public:
    string airlineIATA;
    string airlineID;
    string sourceIATA;
    string sourceID;
    string destIATA;
    string destID;
    string ignore;
    string stops;

    Route(string airlineIATA, string airlineID, string sourceAirportIATA, string sourceAirportID, string destAirportIATA, string destAirportID, string stops);


    static void readRoutesFile();
    static void routeFinder(string inputFile);
    string getSourceCity();
    string getSourceCountry;
    string getDestCity;
    string getDestCountry;
    string findAirlineIATA();
    string getdestAirportIATA();
    string findAllStops();

    static vector<string> bfs(Airport start, Airport destination);
    static vector<string> constructPath(string destinationIATA);
    static void writeFile(string start, string destination, vector<string> path, vector<string> flightPath);
    static bool contains(deque<string> q, string value);
    static bool contains_set(set<string> s, string value);



    static unordered_map<string,vector<Route>> routes;
    static unordered_map<string,vector<Route>> flights;
    static unordered_map<string,string> parentNodes;

};


#endif //SENAXWEPEAFINALCPROJECT_ROUTES_H
