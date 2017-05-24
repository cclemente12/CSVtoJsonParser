#include "hospitalQuery.h"
#include "patientCSV.h"
#include <string.h>

hospitalQuery::hospitalQuery() {
    cout << "Find option:" << endl <<  "\t(1)Type ID" << endl << "\t(2)Name" << endl;
    cin >> option;
    string emptyBuf;
    //this line make sense because getline() get the value of the previous cin.
    //so this getline is just a dummy
    getline(cin, emptyBuf);
    //Enter Option 1
    if(option==1)
    {
            
            cout << "Enter Patient's ID: ";
            //get the patient ID
            getline(cin, input[0]);
            //Go searchInFile function
            fstream file;
            file.open("requestJson.json",ios::out|ios::trunc);
          //  strcpy(temp,"[{Patient ID:"+input[0]+"}]");
            file<<"[{Patient ID:"+input[0]+"}]";
            file.close();
            patientCSV* csv = new patientCSV();
           // searchInFile(temp);
            
    }
//    Enter Option 2
    else
    {
            string temp;
            cout << "Enter Patient's Last Name: ";
            getline(cin, input[0]);
            cout << "Enter Patient's First Name: ";
            getline(cin, input[1]);
            cout << "Enter Patient's Middle Name: ";
            getline(cin, input[2]);
            temp = "[{Last Name:"+input[0]+"},{First Name:"+input[1]+"},{Middle Name:"+input[2]+"}]";
            fstream file;
            file.open("requestJson.json",ios::out|ios::trunc);
            file<<temp;
            file.close();
            patientCSV* csv = new patientCSV();
            
    }
}

hospitalQuery::hospitalQuery(const hospitalQuery& orig) {
}

hospitalQuery::~hospitalQuery() {
}

