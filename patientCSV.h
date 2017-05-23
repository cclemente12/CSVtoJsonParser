#ifndef PATIENTCSV_H
#define PATIENTCSV_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
class patientCSV {
public:
    patientCSV();
    patientCSV(const patientCSV& orig);
    void searchInFile(string* input);
    void searchCSVID(string text);
    void pushToMap();
    void storeInJson();
    void convertToString();
    virtual ~patientCSV();
    
private:
    int option;
    string* input = new string[3];
    string text;
    map<string, string> maps;
    string newData;
    bool flagID=0;
    bool flagFirstData=true;
    vector<string> value;
    vector<string> attribute {"patient ID", "last name", "first name", "middle name", "house number",
                              "street", "city", "province", "birthday", "gender", "blood type", 
                              "weight", "height", " facility id", "health worker id"};
};

#endif /* PATIENTCSV_H */

