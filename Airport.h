//
// Created by Cyril K on 11/20/2022.
//

#ifndef C___INDIVIDUAL_PROJECT_AIRPORT_H
#define C___INDIVIDUAL_PROJECT_AIRPORT_H

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;


class Airport {
private:
    string airportID, name, city, country, iataCode, icaoCode;
    double latitude, longitude;
public:
    static unordered_map<string, vector<Airport>> airports;
    static unordered_map<string, Airport> codes;
    Airport(string id, string name, string city, string country, string iataCode, string icaoCode, double latitude, double longitude);
    static void readFile(string csvFile);
    static vector<Airport> getAirport(string source);
    static Airport getObject(string iataCode);
    string getID();
    string getName();
    string getCountry();
    string getIataCode();
    string getIcaoCode();
    string getCity();
    double getLatitude();
    double getLongitude();



};


#endif //C___INDIVIDUAL_PROJECT_AIRPORT_H
