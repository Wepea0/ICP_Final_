//
// Created by Sena A. Vuvor on 24/11/2022
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Airports.h"
using namespace std;

/**
 * <h2>Implementation of Airport class that contains attributes of airports that are relevant to search</h2>
 * @param airportID
 * @param airportName
 * @param airportCity
 * @param country
 * @param IATA
 * @param ICAO
 * @param latitude
 * @param longitude
 */
Airport::Airport(string airportID, string airportName, string airportCity, string country, string IATA, string ICAO, double latitude, double longitude) {
    this->airportID = airportID;
    this->airportName = airportName;
    this->airportCity = airportCity;
    this->country = country;
    this->IATA = IATA;
    this->ICAO = ICAO;
    this->latitude = latitude;
    this->longitude = longitude;
}

/**
 * <h3>Function that returns the IATA code of a particular airport </h3>
 * @return IATA
 */
string Airport::getIATA() {
    return IATA;
}

/**
 * <h3>Function that returns the LATITUDE of a particular airport </h3>
 * @return latitude of a particular
 */
double Airport::getLatitude() {
    return this->latitude;
}

/**
 * <h3>Function that returns the LONGITUDE of a particular airport </h3>
 * @return Longitude
 */
double Airport::getLongitude() {
    return this->longitude;
}

/**
 * <h3>Function that returns the airports available from a particular airport </h3>
 * @param src
 * @return list of airports
 */
vector<Airport> Airport::getAirport(string source) {
    vector<Airport> portList = Airport::locationtoAirportsMap[source];
    return portList;
}

/**
 * <h3>Function that returns the AIRPORT object when given the IATA code </h3>
 * @param IATA
 * @return Airport object
 */
Airport Airport::getObject(string IATA) {
    Airport tempPort = Airport::airportsMap.at(IATA);
    return tempPort;
}

/**
 * Function to process information from airports file
 */
void Airport::readAirportFile() {

    try{
        ifstream airportReader("airports.csv");

        int count = 0;
        string row;
        string ignore;
        string city;
        string country;
        string iata;
        string stringLatitude;
        string stringLongitude;
        double latitude = 0;
        double longitude = 0;
        char delim = ',';


        while(getline(airportReader, row)){
            if (count == 0){
                count++;
                continue;
            }

            stringstream stream(row);

            getline(stream, ignore, delim);
            getline(stream,ignore, delim);
            getline(stream,city, delim);
            getline(stream,country, delim);
            getline(stream,iata, delim);
            getline(stream,ignore, delim);
            getline(stream,stringLatitude, delim);
            getline(stream,stringLongitude, delim);

            longitude = stod(stringLongitude);
            if (stringLatitude == " ") {continue;}
            else {latitude = stod(stringLatitude);}

            string key = city + ", " + country;
            Airport airportObj = Airport(ignore, ignore, city, country, iata, ignore, latitude, longitude);

            Airport::airportsMap.insert({iata, airportObj});
            vector<Airport> airportsList;

            if (Airport::locationtoAirportsMap.find(key) != Airport::locationtoAirportsMap.end()) {
                vector<Airport> airportsList = Airport::locationtoAirportsMap[key];
                airportsList.push_back(airportObj);
                Airport::locationtoAirportsMap.erase(key);
                Airport::locationtoAirportsMap.insert({key,airportsList});
            } else{
                airportsList.push_back(airportObj);
                Airport::locationtoAirportsMap.insert({key,airportsList});
            }
        }
        airportReader.close();
    } catch (const exception &e){
        cout << "Unable to read or open airports.csv file " << e.what() << endl;
    }
}






