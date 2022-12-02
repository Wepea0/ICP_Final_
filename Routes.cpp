//
// Created by Wepea Buntugu on 24/11/2022
//

/**
 *  * <h2>Route class implementation</h2>
 * <h3>Implementation of Route class that contains relevant route information for route searches</h3>
 */
#include "Routes.h"
#include<bits/stdc++.h>
#include <set>
#include <iostream>
#include <queue>

using namespace std;

/**
 * <h2>Route object constructor </h2>
 * @param airlineIATA
 * @param airlineID
 * @param sourceAirportIATA
 * @param sourceAirportID
 * @param destAirportIATA
 * @param destAirportID
 * @param stops
 */
Route::Route(string airlineIATA, string airlineID, string sourceAirportIATA, string sourceAirportID, string destAirportIATA, string destAirportID, string stops) {
    this->airlineIATA = airlineIATA;
    this->airlineID = airlineID;
    this->sourceIATA = sourceAirportIATA;
    this->sourceID = sourceAirportID;
    this->destIATA = destAirportIATA;
    this->destID = destAirportID;
    this->stops = stops;
}

/**
 * <h3>Read Routes File</h3>
 * Processes information from routes csv file
 */
void Route::readRoutesFile() {
    try{
        string row;
        string airlineIATA;
        string airlineID;
        string sourceAirportIATA;
        string sourceAirportID;
        string destAirportIATA;
        string destAirportID;
        string ignore;
        string stops;
        char delim = ',';

        ifstream routeFileReader("routes.csv");

        while(getline(routeFileReader, row)) {
            stringstream stream(row);

            getline(stream, airlineIATA, delim);
            getline(stream, airlineID, delim);
            getline(stream, sourceAirportIATA, delim);
            getline(stream, sourceAirportID, delim);
            getline(stream, destAirportIATA, delim);
            getline(stream, destAirportID, delim);
            getline(stream, ignore, delim);
            getline(stream, stops, delim);

            string locationKey = sourceAirportIATA + "," + destAirportIATA;
            string key = sourceAirportIATA;
            Route routeObj = Route(airlineIATA, airlineID, sourceAirportIATA, sourceAirportID, destAirportIATA, destAirportID, stops);
            vector<Route> flightList;
            vector<Route> routeList;

            if (Route::flights.find(locationKey) != Route::flights.end()){
                vector<Route> flightList = Route::flights[locationKey];
                flightList.push_back(routeObj);
                Route::flights.erase(locationKey);
                Route::flights.insert({locationKey,flightList});
            } else {
                flightList.push_back(routeObj);
                Route::flights.insert({locationKey,flightList});
            }

            if (Route::routes.find(key) != Route::routes.end()){
                vector<Route> routeList = Route::routes[key];
                routeList.push_back(routeObj);
                Route::routes.erase(key);
                Route::routes.insert({key,routeList});
            } else{
                routeList.push_back(routeObj);
                Route::routes.insert({key,routeList});
            }
        }
        routeFileReader.close();
    } catch (const exception &e){
        cout << "Unable to open or read routes.csv file " << e.what() << endl;
    }
}

/**
 * <h2>Route Finder </h2>
 * Reads information (start and destination) from a file and calculates optimal route
 * @param inputFile
 */
void Route::routeFinder(string inputFile) {
    vector<string> query;
    Airport::readAirportFile();
    readRoutesFile();
    char delim = ',';

    try{
        string row;
        string city;
        string country;
        string destinationCity;
        string destinationCountry;

        ifstream fileStream(inputFile);
        while (getline(fileStream,row)){
            stringstream stream(row);
            getline(stream, city, delim);
            getline(stream, country, delim);
            query.push_back(city);
            query.push_back(country);
        }
        fileStream.close();
    } catch (const exception &e){
        cout << "Unable to open or read airports file " << e.what() << endl;
    }

    string source = query.at(0) + delim + query.at(1);
    string finalDestination = query.at(2) + delim + query.at(3);

    vector<Airport> sourceAirports = Airport::getAirport(source);
    vector<Airport> destinationAirports = Airport::getAirport(finalDestination);

    vector<string> path;
    vector<string> flightPath;
    vector<double> distances;
    unordered_map<double, vector<string>> pathDistance;
    for (int i = 0; i < destinationAirports.size(); i++){

        if (destinationAirports.at(i).getIATA() == "\\N")
            continue;
        for (int j = 0; j < sourceAirports.size(); j++){
            if (sourceAirports.at(j).getIATA() == "\\N")
                continue;
            path = bfs(sourceAirports.at(j),destinationAirports.at(i));
            double distance = 0;
            for (int k = 0; k < path.size()-1; k++) {
                Airport start = Airport::getObject(path.at(k));
                Airport destination = Airport::getObject(path.at(k+1));
            }
            distances.push_back(distance);
            pathDistance.insert({distance, path});
            for (string p: path)
                cout << p << " ";
            cout << endl;
        }
    }

    double minDistance = *min_element(distances.begin(), distances.end());
    path = pathDistance[minDistance];

    for (int k = 0; k < path.size()-1; k++){
        string key = path.at(k) + "," + path.at(k+1);

        if(Route::flights.find(key) != Route::flights.end()){
            string current = Route::flights[key].at(0).findAirlineIATA();
            flightPath.push_back(current);
        }
    }
    Route::writeFile(query.at(0), query.at(2), path, flightPath);
}

/**
 * <h2> Find AirlineIATA </h2>
 * Returns the AirlineIATA
 * @return airlineIATA
 */
string Route::findAirlineIATA() {
    return this->airlineIATA;
}


/**
 * <h2> Get Destination Airport IATA </h2>
 * Returns the Destination airport IATA
 * @return destIATA
 */
string Route::getdestAirportIATA() {
    return this->destIATA;
}


/**
 * <h2> Find All Stops </h2>
 * Returns the stops along this route
 * @return stops
 */
string Route::findAllStops() {
    return this->stops;
}


/**
 * <h2>Contains </h2>
 * Helper method for checking if a particular value exists in a deque
 * @param myDeque
 * @param value
 * @return true or false
 */
bool Route::contains(deque<string> myDeque, string value) {
    deque<string>::iterator itr;
    itr = find(myDeque.begin(), myDeque.end(), value);
    if(itr != myDeque.end()) {return true;}
    else {return false;}
}

/**
 * <h2>Contains </h2>
 * Helper method for checking if a particular value exists in a set
 * @param s
 * @param value
 * @return true or false
 */
bool Route::contains_set(set<string> s, string value) {
    auto pos = s.find(value);
    if(pos != s.end()) {return true;}
    else {return false;}

}







