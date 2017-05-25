#ifndef PATIENTCSV_H
#define PATIENTCSV_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <string.h>
#include "XML.h"
using namespace std;
class patientCSV {
public:
    patientCSV();
    patientCSV(const patientCSV& orig);
    void searchInFile();
    void searchCSVID(string text);
    void pushToMap();
    void getAttribute();
    void storeInJson();
    void inputToJson();
    bool healthWorker();
    bool facilityDBSearch();
    bool searchInFacilityDB(int pos);
    void convertToString();
    virtual ~patientCSV();
    //Added 2 function
    void convertToCSV();
    void editDataCSV();
    
private:
    char *dup;
    char *pch;
    int option;
    string buffer;
    string* input = new string[5];
    string text;
    map<string, string> maps;
    string newData;
    bool flagID=0;
    bool flagFirstData=true;
    vector<string> request;
    vector<string> value;
    vector<string> attribute {"patient ID", "last name", "first name", "middle name", "house number",
                              "street", "city", "province", "birthday", "gender", "blood type", 
                              "weight", "height", " facility id", "health worker id"};
};

#endif /* PATIENTCSV_H */

