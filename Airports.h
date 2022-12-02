//
// Created by Sena A. Vuvor on 23/11/2022.
//

#ifndef SENAXWEPEAFINALCPROJECT_AIRPORTS_H
#define SENAXWEPEAFINALCPROJECT_AIRPORTS_H

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * <h2>Airport class definitions</h2>
 */
class Airport {
public:
    string airportID;
    string airportName;
    string airportCity;
    string country;
    string IATA;
    string ICAO;
    double longitude;
    double latitude;
    static unordered_map<string, vector<Airport>> locationtoAirportsMap;
    static unordered_map<string, Airport> airportsMap;

    string getIATA();
    double getLatitude();
    double getLongitude();
    static vector<Airport> getAirport(string source);
    static Airport getObject(string IATA);
    static void readAirportFile();

    Airport(string airportID, string airportName, string airportCity, string country,
            string IATA, string ICAO, double latitude, double longitude);
};


#endif //SENAXWEPEAFINALCPROJECT_AIRPORTS_H
