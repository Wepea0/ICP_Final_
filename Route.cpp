#include "Route.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <multinfo.h>
#include <cmath>
#include<bits/stdc++.h>
#include <set>

using namespace std;


Routes::Routes(string airlineIata, string airlineId, string sourceIata,
             string sourceId, string destIata, string destId,
              string stops) {
    this->airlineIata = airlineIata;
    this->airlineId = airlineId;
    this->sourceIata = sourceIata;
    this->sourceId = sourceId;
    this->destIata = destIata;
    this->destId = destId;
    this->stops = stops;
}


void Routes::findAllFlights(string csvFile) {
    ifstream fileStream;

    try{
        fileStream.open(csvFile);

        string line;
        string airlineIata;
        string airlineId;
        string sourceAirportId;
        string destAirportIata;
        string destAirportId;
        string codeshare;
        string stops;
        string sourceAirportIata;


        while(getline(fileStream, line)) {
            //Try and skip the first line of file
            stringstream stream(line);

            getline(stream, airlineIata, ',');
            getline(stream, airlineId, ',');
            getline(stream, sourceAirportIata, ',');
            getline(stream, sourceAirportId, ',');
            getline(stream, destAirportIata, ',');
            getline(stream, destAirportId, ',');
            getline(stream, codeshare, ',');
            getline(stream, stops, ',');



            string compKey = sourceAirportIata + "," + destAirportIata;
            Routes tempRoute = Routes(airlineIata,airlineId,sourceAirportIata,sourceAirportId,destAirportIata,destAirportId,stops);

            if (Routes::flights.find(compKey) != Routes::flights.end()){
                vector<Routes> flightList = Routes::flights[compKey];
                flightList.emplace_back(tempRoute);
                Routes::flights.erase(compKey);
                Routes::flights.insert({compKey,flightList});
            }
            else{
                vector<Routes> flightList;
                flightList.emplace_back(tempRoute);
                Routes::flights.insert({compKey,flightList});
            }

            string key = sourceAirportIata;
            if (Routes::routes.find(key) != Routes::routes.end()){
                vector<Routes> routeList = Routes::routes[key];
                routeList.emplace_back(tempRoute);
                Routes::routes.erase(key);
                Routes::routes.insert({key,routeList});
            }
            else{
                vector<Routes> routeList;
                routeList.emplace_back(tempRoute);
                Routes::routes.insert({key,routeList});
            }
        }

    }
    catch (std::exception const& e){
        cout << "There was an error: " << e.what() << endl;
    }
    fileStream.close();

}



void Routes::findRoute(std::string csvFile) {
    Airport::readFile("airports.csv");
    ifstream fileStream;
    vector<string> list;

    try{
        string line,city, country, destinationCity, destinationCountry;

        fileStream.open(csvFile);
        while (getline(fileStream,line)){
            stringstream stream(line);
            getline(stream,city,',');
            getline(stream, country,',');
            list.emplace_back(city);
            list.emplace_back(country);
        }

    }
    catch (std::exception const& e){
        cout << "There was an error: " << e.what() << endl;
    }
    fileStream.close();
    string sourceCity = list.at(0);
    string sourceCountry = list.at(1);
    string destCity = list.at(2);
    string destCountry = list.at(3);
    string source = sourceCity + "," + sourceCountry;
    string dest = destCity + "," + destCountry;


    findAllFlights("routes.csv");


    vector<Airport> sourceAirports = Airport::getAirport(source);
    vector<Airport> destinationAirports = Airport::getAirport(dest);

    //Check for null values
    vector<string> path;
    vector<string> flightPath;
    vector<double> distances;
    unordered_map<double, vector<string>> pathDistance;
    for (int i = 0; i < destinationAirports.size(); i++){

        if (destinationAirports.at(i).getIataCode() == "\\N")
            continue;
        for (int j = 0; j < sourceAirports.size(); j++){
            if (sourceAirports.at(j).getIataCode() == "\\N")
                continue;
            path = bfs(sourceAirports.at(j),destinationAirports.at(i));
            double distance = 0;
            for (int k = 0; k < path.size()-1; k++) {
                Airport start = Airport::getObject(path.at(k));
                Airport destination = Airport::getObject(path.at(k+1)); //Airport::codes.at(path.at(k + 1));
                distance += calcHaversineDist(start,destination);

            }
            distances.emplace_back(distance);
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

        if(Routes::flights.find(key) != Routes::flights.end()){
            string current = Routes::flights[key].at(0).getAirlineIata();  //Picking the first available flight from one location to another
            flightPath.emplace_back(current);
        }
    }
    Routes::writeFile(sourceCity, destCity, path, flightPath, minDistance);

}


vector<string> Routes::bfs(Airport start, Airport destination) {
    set<string> explored;
    deque<string> frontier;
    frontier.push_back(start.getIataCode());
    parents.insert({start.getIataCode(), "None"});



    while(!frontier.empty()){
        string poppedValue = frontier.front();
        explored.insert(poppedValue);
        frontier.pop_front();

        if(Routes::routes.find(poppedValue) != Routes::routes.end()){
            vector<Routes> temp = Routes::routes[poppedValue];
            for(int i = 0; i < temp.size(); i++){
                Routes child = temp.at(i);

                if (!Routes::contains(frontier,child.findDestIATA()) and !Routes::contains_set(explored,child.findDestIATA())){
                    if(Routes::parents.find(child.findDestIATA()) == Routes::parents.end()) {
                        Routes::parents.insert({child.findDestIATA(), poppedValue});
                    }
                    if (child.findDestIATA() == destination.getIataCode()) {
                        return solutionPath(child.destIata);
                    }
                    frontier.push_back(child.findDestIATA());
                }

            }

        }

    }

}




string Routes::getAirlineIata() {
    return this->airlineIata;
}



string Routes::getAirlineId() {
    return this->airlineId;
}


string Routes::getSourceId() {
    return this->sourceId;
}


string Routes::findDestIATA() {
    return this->destIata;
}





bool Routes::contains(deque<string> myDeque, string value) {
        deque<string>::iterator itr;
        itr = find(myDeque.begin(), myDeque.end(), value);
        if(itr != myDeque.end()) {
            return true;
        }
        else
            return false;

}



/**
 * This function checks whether a set contains a particular value
 * @param s The set
 * @param value The value being checked for
 * @return whether the set contains the value or not
 */
bool Routes::contains_set(set<string> s, string value) {
    auto pos = s.find(value);

    if(pos != s.end())
        return true;
    else
        return false;

}


vector<string> Routes::solutionPath(string destinationIata) {
    vector<string> path;
    path.emplace_back(destinationIata);
    string current = destinationIata;

    while(Routes::parents.find(current) != Routes::parents.end()){
        current = parents[current];
        if (current == "None"){
            break;
        }
        else{
            path.emplace_back(current);
        }
    }
    reverse(path.begin(), path.end());
    return path;
}



void Routes::writeFile(string start, string destination, vector<string> path, vector<string> flightPath, double distance) {
    ofstream fileStream;
    start[0] = tolower(start[0]);
    destination[0] = tolower(destination[0]);
    try{
        string filename = start + "-" + destination + "_output.txt";
        fileStream.open(filename);

        int count  =  0;
        int numStops = 0;
        while (count < path.size()-1){
            string key = path.at(count) + "," + path.at(count+1);
            vector<Routes> route = Routes::flights[key];
            string stops = route.at(0).findAllStops(); //Getting the number of stops for the first flight taken, corresponding to the first flight selected earlier
            fileStream << count+1 << ". " << flightPath.at(count) + " from " + path.at(count) + " to " + path.at(count+1) + " " + stops + " stops" << endl;
            numStops += stoi(stops);
            count++;

        }

        int numFlights = path.size()-1;
        fileStream << "Total flights = " << numFlights << endl;
        fileStream << "Total additional stops = " << numStops << endl;
        fileStream << "Total distance: " << distance << "km" << endl;
        fileStream << "Optimality criteria: distance";


    }
    catch (std::exception const& e){
        cout << "There was an error: " << e.what() << endl;
    }
    fileStream.close();


}


double Routes::calcHaversineDist(Airport start, Airport destination) {
    double startLatitude, destinationLatitude, startLongitude, destinationLongitude;

    startLatitude = start.getLatitude();
    startLongitude = start.getLongitude();
    destinationLatitude = destination.getLatitude();
    destinationLongitude = destination.getLongitude();

    double latitudeDistance = (destinationLatitude - startLatitude) * M_PI / 180.0;
    double longitudeDistance = (destinationLongitude - startLongitude) * M_PI/ 180.0;

    startLatitude = (startLatitude) * M_PI / 180.0;
    destinationLatitude = (destinationLatitude) * M_PI / 180.0;

    double temp = pow(sin(latitudeDistance / 2), 2) + pow(sin(longitudeDistance / 2), 2) * cos(startLatitude) * cos(destinationLatitude);

    double rad = 6371;
    double x = 2 * asin(sqrt(temp));
    double result = rad * x;

    return result;

}

string Routes::findAllStops() {
    return this->stops;
}



