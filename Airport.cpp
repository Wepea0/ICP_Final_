//
// Created by Wepea Buntugu on 23/11/2022.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "AirportCpp.h"

using namespace std;

class Airport::Airport{
public:
    /* Declaration of instance variables */
    string airportID;
    string airportName;
    string airportCity;
    string country;
    string IATA;
    string ICAO;
    double longitude;
    double latitude;

    /* Method declarations */
    string toString();
    string getAirportID();
    void setAirportID(string AirportID);
    void setIATA(string IATA);
    string getIATA() ;
    void setICAO(string ICAO);
    string getICAO() ;
    string getAirportCity();
    void setAirportCity(string airportCity);
    string getAirportName();
    void setAirportName(string airportName);
    string getCountry();
    void setCountry(string country);
    double getLongitude();
    void setLongitude(double longitude);
    double getLatitude();
    void setLatitude(double latitude);

    void readAirportFile(string airportFile);
    Airport getObject(string IATA);
    vector<Airport> getAirport(string source);


    /** Constructor method for Airport class
     *@param: string airportID;
     *        string airportName;
     *        string airportCity;
     *        string country;
     *        string IATA;
     *        string ICAO;
     *        double longitude;
    *         double latitude;
    **/
    Airport(string ID, string name, string city, string country, string IATA, string ICAO, double airlong, double lat) {
        this->airportID = ID;
        this -> airportName = name;
        this -> airportCity = city;
        this -> country = country;
        this -> IATA = IATA;
        this -> ICAO = ICAO;
        this -> longitude = airlong;
        this -> latitude = lat;
    }

};


/**
 * toString method to write aiport object as a string for readability
 * @returns: string
 * */
string Airport::toString(){
    return this->airportID + " name= " + airportName + " city= " + airportCity + " country= " + country + " IATA code= " + ICAO;
}

/**
 * Accessor and Mutator Methods for the instance variables
 * */
string Airport::getAirportID(){
    return airportID;
};

void Airport::setAirportID(string airportID){
    this -> airportID = airportID;
}

string Airport::getAirportCity() {
    return airportCity;
}

void Airport::setAirportCity(string airportCity) {
    this->airportCity = airportCity;
}

string Airport::getAirportName() {
    return airportName;
}

void Airport::setAirportName(string airportName) {
    this->airportName = airportName;
}

string Airport::getCountry() {
    return country;
}

void Airport::setCountry(string country) {
    this -> country = country;
}

string Airport::getIATA() {
    return IATA;
}

void Airport::setIATA(string IATA) {
    this -> IATA = IATA;
}

string Airport::getICAO() {
    return ICAO;
}

void Airport::setICAO(string ICAO) {
    this -> ICAO = ICAO;
}

double Airport::getLongitude() {
    return longitude;
}

void Airport::setLongitude(double longitude) {
    this -> longitude = longitude;
}

double Airport::getLatitude() {
    return latitude;
}

void Airport::setLatitude(double latitude) {
    this -> latitude = latitude;
}

/**
 * Additional accessor method to fetch list of airports from map of airports in every location
 * @param: srcAirport
 * @return: vector<Airport>
 * */
vector<Airport> Airport::getAirport(string srcAirport) {
    vector<Airport> airportList = Airport::locationtoAirportsMap[srcAirport];
    return airportList;
}

/**
 * Additional accessor method to fetch airport object from unordered map of airports
 * @param: IATA
 * @return: Airport object
 * */
Airport Airport::getObject(string IATA) {
    Airport newAirport = Airport::airportsMap.at(IATA);
    return newAirport;
}


/**
 * Method to read airports.csv file and store data in unordered map
 * @param: airportFile
 */
void Airport::readAirportFile(string airportFile) {
    ifstream airportReader(airportFile);

    try{

        string values;
        int count = 0;
        string row;

        string airportID;
        string airportName;
        string city;
        string country;
        string IATA;
        string ICAO;
        string airLong;
        string airLat;
        char delim = ',';

        double longitude, latitude;


        while(getline(airportReader, row)){
            if (count == 0){
                count++;
                continue;
            }
            stringstream input(row);

            getline(input, airportID, delim);
            getline(input, airportName, delim);
            getline(input, city, delim);
            getline(input, country, delim);
            getline(input, IATA, delim);
            getline(input, ICAO, delim);
            getline(input, airLong, delim);
            getline(input, airLat, delim);

            longitude = stod(airLong);

            if (airLat == " ")
                latitude = 0.0;
            else
                latitude = stod(airLat);


            string key = city + ", " + country;

            Airport airport = Airport(airportID, airportName, city, country, IATA, ICAO, latitude, longitude);

            Airport::airportsMap.insert({IATA, airport});
            vector<Airport> airportsList;

            if (Airport::locationtoAirportsMap.find(key) != Airport::locationtoAirportsMap.end()) {
                airportsList = Airport::locationtoAirportsMap[key];
                airportsList.push_back(airport);
                Airport::locationtoAirportsMap.erase(key);
                Airport::locationtoAirportsMap.insert({key, airportsList});
            }
            else{
                airportsList.push_back(airport);
                Airport::locationtoAirportsMap.insert({key, airportsList});
            }
        }
        airportReader.close();

    } catch (const exception &e){
        cout << "Unable to open or read airports.csv file." << e.what() << endl;
    }

}
