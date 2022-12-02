//
// Created by Sena A. Vuvor on 24/11/2022
//



#include <iostream>
#include "Airports.h"
#include "Routes.h"
#include<bits/stdc++.h>
using namespace std;

/**
 * Helper variables for search program
 */
unordered_map<string, Airport> Airport::airportsMap = *new unordered_map<string, Airport>;
unordered_map<string, vector<Airport>> Airport::locationtoAirportsMap = *new unordered_map<string, vector<Airport>>;
unordered_map<string, vector<Route>> Route::routes = *new unordered_map<string, vector<Route>>;
unordered_map<string, vector<Route>> Route::flights = *new unordered_map<string, vector<Route>>;
unordered_map<string, string> Route::parentNodes = *new unordered_map<string, string>;


/**
 * <h2>Construct Path </h2>
 * Reconstructs the path taken from a start airport to a destination
 * @param destinationIATA
 * @return
 */
vector<string> Route::constructPath(string destinationIATA) {
    vector<string> path;
    path.push_back(destinationIATA);
    string current = destinationIATA;

    while(Route::parentNodes.find(current) != Route::parentNodes.end()){
        current = parentNodes[current];
        if (current == "None") {
            break;
        } else {
            path.push_back(current);
        }
    }
    reverse(path.begin(), path.end());
    return path;
}


/**
 * <h2> Breadth-first search (bfs) </h2>
 * Examines possible routes using breadth-first search algorithm
 * @param source
 * @param destination
 * @return List of route objects showing the path taken
 */
vector<string> Route::bfs(Airport source, Airport destination) {
    deque<string> frontier;
    set<string> explored;
    frontier.push_back(source.getIATA());
    parentNodes.insert({source.getIATA(), "None"});

    while(!frontier.empty()){
        string poppedValue = frontier.front();
        frontier.pop_front();
        explored.insert(poppedValue);

        if(Route::routes.find(poppedValue) != Route::routes.end()){
            vector<Route> temp = Route::routes[poppedValue];
            for(int i = 0; i < temp.size(); i++){
                Route child = temp.at(i);

                if (!Route::contains(frontier,child.getdestAirportIATA()) and !Route::contains_set(explored,child.getdestAirportIATA())){
                    if(Route::parentNodes.find(child.getdestAirportIATA()) == Route::parentNodes.end()) {
                        Route::parentNodes.insert({child.getdestAirportIATA(), poppedValue});
                    }
                    if (child.getdestAirportIATA() == destination.getIATA()) {
                        return constructPath(child.destIATA);
                    }
                    frontier.push_back(child.getdestAirportIATA());
                }
            }
        }
    }
}

/**
 * <h2>Write File </h2>
 * Write the returned routes list to a file
 * @param start
 * @param destination
 * @param path
 * @param flightPath
 */
void Route::writeFile(string start, string destination, vector<string> path, vector<string> flightPath) {

    try{
        string filename = start + "-" + destination + "_Output.txt";
        ofstream fileWriter(filename);

        int numStops = 0;
        int count  =  0;

        while (count < path.size()-1){
            string key = path.at(count) + "," + path.at(count+1);
            vector<Route> route = Route::flights[key];
            string stops = route.at(0).findAllStops();
            fileWriter << count+1 << ". " << flightPath.at(count) + " from " +
                                             path.at(count) + " to " + path.at(count+1)
                                             + ", " + stops + " stops" << endl;
            numStops = numStops + stoi(stops);
            count++;
        }

        int numFlights = path.size()-1;
        fileWriter << "Total number of flights = " << numFlights << endl;
        fileWriter << "Total number of stops = " << numStops << endl;
        fileWriter.close();
    } catch (const exception &e){
        cout << "Unable to write into new file " << e.what() << endl;
    }
}

int main() {
    Route::routeFinder("input.txt");
}

