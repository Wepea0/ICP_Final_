#include <iostream>
#include "Airport.h"
#include <iostream>
#include <unordered_set>
#include "Route.h"

using namespace std;

unordered_map<string, vector<Airport>> Airport::airports = *new unordered_map<string, vector<Airport>>;
unordered_map<string, vector<Routes>> Routes::flights = *new unordered_map<string, vector<Routes>>;
unordered_map<string, Airport> Airport::codes = *new unordered_map<string, Airport>;
unordered_map<string, vector<Routes>> Routes::routes = *new unordered_map<string, vector<Routes>>;
unordered_set<string> hold_source_airports = *new unordered_set<string>;
unordered_map<string, string> Routes::parents = *new unordered_map<string, string>;



int main() {
    Routes::findRoute("Accra_Brussels.txt");
}


