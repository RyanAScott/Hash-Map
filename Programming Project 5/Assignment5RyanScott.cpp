#include <iostream>
#include <fstream>
#include <map>
#include "OpenRecord.h"
using namespace std;

typedef map<string, OpenRecord> airportMap;

void doInputDataFromFile(airportMap& airplaneData)
{
    // importing the air16.txt file
   string filename = "air16.txt";
   ifstream infile(filename);
   OpenRecord r;
   int dataSize;

   // Exception for if the file isn't there
   if (!infile) {
       cout << "Unable to open file";
       exit(1);
   }// if 

   // opening the file
   if (infile.is_open()) {
       // the dataSize is the number at the start of the file '16', 
       // which specifys the map size
       infile>>dataSize;
       for (int j = 0; j < dataSize; j++) {
           infile>>r.code;
           infile>>r.name;
           infile>>r.city;
           infile>>r.country;
           infile>>r.latitudeDeg;
           infile>>r.latitudeMin;
           infile>>r.latitudeSec;
           infile>>r.latitudeDir;
           infile>>r.longitudeDeg;
           infile>>r.longitudeMin;
           infile>>r.longitudeSec;
           infile>>r.longitudeDir;
           infile>>r.altitude;

           airplaneData[r.code] = r;
       } // for
       // closing file
       infile.close();
        
   } // if
 } // doInputDataFromFile

void addRecord(OpenRecord& r) {
    cout << "input record data in following order: " << endl;
    cout << "(code, name, city, country, latitudeDegrees, latitudeMinutes, latitudeSeconds, ";
    cout << "latitudeDirection, longitudeDegrees, longitudeMinutes, longitudeSeconds, ";
    cout << "longitudeDirection, altitude)" << endl;
    // cin functions like the Scanner in Java, accecpting inputs
    cin>>r.code;
    cin>>r.name;
    cin>>r.city;
    cin>>r.country;
    cin>>r.latitudeDeg;
    cin>>r.latitudeMin;
    cin>>r.latitudeSec;
    cin>>r.latitudeDir;
    cin>>r.longitudeDeg;
    cin>>r.longitudeMin;
    cin>>r.longitudeSec;
    cin>>r.longitudeDir;
    cin>>r.altitude;
} // addRecord

void outputMap(airportMap map) {
    cout << "{" << endl;
    for(airportMap::iterator it = map.begin(); it != map.end(); ++it)
        cout<< "(" << it->first << "," << it->second << ")" << endl;
    
    cout << "}" << endl;
}// outputMap

void mapSize(airportMap map) {
    cout << "Number of records in map: " << map.size() << endl;
}// mapSize

void recordCheck(string key, airportMap map) {
        if(map.count(key) > 0)
            cout << key << " has a record" << endl;
        else
            cout << key << " does not exist in current map" << endl;
}//recordCheck

void removeKey(string key, airportMap& map) {
    if(map.count(key) > 0)
        map.erase(key);
    else
        cout << key << " does not exist in current map" << endl;    
}// removeKey

void recordSwap(string targetKey, OpenRecord newRec, airportMap& map) {    
    if(map.count(targetKey) > 0) {
        removeKey(targetKey, map);
        map[newRec.code] = newRec;
    }
}// recordSwap

int main() {
    airportMap m1;
    OpenRecord rec;

    doInputDataFromFile(m1); // putting data into map and keys into sequence
    outputMap(m1); // outputing map 
    mapSize(m1); // oupting size 
    recordCheck("YWG", m1); // checking for record/key existence 
    recordCheck("CMB", m1); // checking for record/key existence 
    cout << "Removing HND\n";
    removeKey("HND", m1); // removing record with key in map 
    mapSize(m1); // oupting size 
    outputMap(m1); // outputing map after the remove 
    cout << "To replace CFS with SYD, please follow the instructions below\n";
    addRecord(rec); // adding in record
    recordSwap("CFS", rec, m1); // swapping records 
    cout << "Success! CFS has been successfully swapped!\n";
    cout << "Plz check the map below\n";
    outputMap(m1); // outputing map 
    mapSize(m1); // oupting size 

    return 0;
}// main