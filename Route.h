
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <multinfo.h>
#include <deque>
#include <queue>
#include <set>
#include "Airport.h"
using namespace std;

/**
 * <h2>Class for route objects. This contains attributes for the route information that is most relevant to
 * the bfs search process </h2>
 */
class Routes {
private:
    string airlineId;
    string sourceIata;
    string destId;
    string airlineIata;
    string stops;
    string sourceId;
    string destIata;


public:
    static unordered_map<string,vector<Routes>> routes;
    static unordered_map<string,vector<Routes>> flights;
    static unordered_map<string,string> parents;
    static unordered_set<string> hold_source_airports;


    Routes(string airlineIata,
          string airlineId,
          string sourceIata,
          string sourceId,
          string destIata,
          string destId,
          string stops);

    static void findRoute(string csvFile);
    static vector<string> bfs(Airport start, Airport destination);
    static double calcHaversineDist(Airport start, Airport destination);
    static void writeFile(string start, string destination, vector<string> path, vector<string> flightPath, double distance);
    static bool contains(deque<string> q, string value);
    static bool contains_set(set<string> s, string value);
    static vector<string> solutionPath(string destinationIata);
    static void findAllFlights(string csvFile);

    string getAirlineIata();
    string getAirlineId();
    string getSourceId();
    string findDestIATA();
    string findAllStops();



};


