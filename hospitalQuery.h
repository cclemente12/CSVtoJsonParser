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
private:
        string* input = new string[3];
        int option;
};

#endif /* HOSPITALQUERY_H */


