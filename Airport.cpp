/**
 * This class represents an Airport object
 * @author Cyril Kujar & Bernd Opoku-Boadu
 */

#include "Airport.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


/**
 * Constructor for airport object.
 * @param id The unique id of the airport
 * @param name The name of the airport
 * @param city The city the airport is located in
 * @param country The country the airport is located in
 * @param iataCode The unique IATA code for the airport
 * @param icaoCode The unique ICAO code for the airport
 * @param latitude The latitude at that location
 * @param longitude The longitude at that location
 */
Airport::Airport(string id, string name, string city, string country, string iataCode, string icaoCode, double latitude, double longitude) {
    this->airportID = id;
    this->name = name;
    this->city = city;
    this->country = country;
    this->iataCode = iataCode;
    this->icaoCode = icaoCode;
    this->latitude = latitude;
    this->longitude = longitude;
}


/**
 * This function gets the name of an airport
 * @return the airport name
 */
string Airport::getName() {
    return this->name;
}

/**
 * This function gets the ID of an airport
 * @return the airport ID
 */
string Airport::getID() {
    return this->airportID;
}

/**
 * This function gets the country an airport is located in
 * @return the airport country
 */
string Airport::getCountry() {
    return this->country;
}


/**
 * This function gets the IATA code of an airport
 * @return unique airport IATA code
 */
string Airport::getIataCode() {
    return iataCode;
}

/**
 * This function gets the ICAO code of an airport
 * @return unique airport ICAO code
 */
string Airport::getIcaoCode() {
    return this->icaoCode;
}

/**
 * This function gets the city an airport is located in
 * @return airport city
 */
string Airport::getCity() {
    return this->city;
}


/**
 * This function reads a csv file, creates airport objects with its values and stores them in unordered maps for later access.
 * @param csvFile the airports csv file being read.
 */
void Airport::readFile(string csvFile) {
    ifstream fileStream;

    try{
        fileStream.open(csvFile);
        string line, id, name, city, country, iata, icao, tempLatitude, tempLongitude;
        double latitude = 0, longitude;
        int count = 0;


        while(getline(fileStream, line)){
            if (count == 0){
                count++;
                continue;
            }
            stringstream stream(line);

            getline(stream, id, ',');
            getline(stream,name,',');
            getline(stream,city,',');
            getline(stream,country,',');
            getline(stream,iata,',');
            getline(stream,icao,',');
            getline(stream,tempLatitude,',');
            getline(stream,tempLongitude,',');

            if (tempLatitude == " ")
                continue;

            else
                latitude = stod(tempLatitude);

            longitude = stod(tempLongitude);



            string key = city + ", " + country;
            Airport tempAirport = Airport(id, name, city, country, iata, icao, latitude, longitude);

            Airport::codes.insert({iata, tempAirport});

            if (Airport::airports.find(key) != Airport::airports.end()) {
                vector<Airport> tempList = Airport::airports[key];
                tempList.emplace_back(tempAirport);
                Airport::airports.erase(key);
                Airport::airports.insert({key,tempList});
            }
            else{
                vector<Airport> tempList;
                tempList.emplace_back(tempAirport);
                Airport::airports.insert({key,tempList});
            }

        }

    }

    catch (std::exception const& e){
        cout << "There was an error: " << e.what() << endl;
    }
    fileStream.close();


}

/**
 * This function gets all the airports in a particular city
 * @param source the source city, country
 * @return A vector of airports from that city
 */
vector<Airport> Airport::getAirport(string source) {
    vector<Airport> portList = Airport::airports[source];
    return portList;
}

/**
 * This function gets the airport associated with a particular IATA code
 * @param iataCode unique IATA code of airport
 * @return airport object associated with code
 */
Airport Airport::getObject(string iataCode) {
    Airport tempPort = Airport::codes.at(iataCode);
    return tempPort;
}


/**
 * This function gets the latitude value of an Airport
 * @return Airport latitude
 */
double Airport::getLatitude() {
    return this->latitude;
}

/**
 * This function gets the longitude value of an airport
 * @return Airport longitude
 */
double Airport::getLongitude() {
    return this->longitude;
}




