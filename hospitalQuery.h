#ifndef HOSPITALQUERY_H
#define HOSPITALQUERY_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class hospitalQuery {
public:
    hospitalQuery();
    hospitalQuery(const hospitalQuery& orig);
    virtual ~hospitalQuery();
    void readJson();
private:
        string* input = new string[3];
        int option;
        int flag=0;//Editted
        
};

#endif /* HOSPITALQUERY_H */


