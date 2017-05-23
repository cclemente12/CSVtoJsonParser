#include "patientCSV.h"
char pastChar;

patientCSV::patientCSV() {
    cout << "Find option:" << endl <<  "\t(1)Type ID" << endl << "\t(2)Name" << endl;
    cin >> option;
    string emptyBuf;
    getline(cin, emptyBuf);
    if(option==1)
    {
            cout << "Enter Patient's ID: ";
            getline(cin, input[0]);
            flagID=0;
            searchInFile(input);
            storeInJson();
            
    }
    else
    {
            cout << "Enter Patient's Last Name: ";
            getline(cin, input[0]);
            cout << "Enter Patient's First Name: ";
            getline(cin, input[1]);
            cout << "Enter Patient's Middle Name: ";
            getline(cin, input[2]);
            flagID=1;
            searchInFile(input);
            storeInJson();
    }
    
}

patientCSV::patientCSV(const patientCSV& orig) {
}

patientCSV::~patientCSV() {
}

void patientCSV::searchInFile(string* input)
{
    fstream file;
    file.open("patient.csv", ios::in);
    while(!file.eof())
    {
        getline(file,text);
        searchCSVID(text);
    }
    file.close();
}


void patientCSV::searchCSVID(string text)
{
  string temporary;
  int ctr=0;
    for(auto i=text.begin() ; i != text.end(); ++i) 
    {   
        if((*i) == ',' && pastChar == ',')
        {
            temporary += "";
        }
        
        if((*i) != ',')
        {
            temporary += (*i);
        }
        
        if ((*i) == ',')
        {
            ctr++;
            if(input[0]!=temporary&&ctr==1&&flagID==0)
                return;
            else if(((input[0]!=temporary&&ctr==2) || (input[1]!=temporary&&ctr==3) || (input[2]!=temporary&&ctr==4))&&flagID==1){
                value.clear();
                return;
            }
            value.push_back(temporary);
            temporary.clear();
        }
        
        pastChar = (*i);
    }
    value.push_back(temporary);
    pushToMap();   
}

void patientCSV::pushToMap(){ // MAP THE KEY-VALUE PAIR
    for(unsigned int i = 0; i < attribute.size(); i++){
        maps.insert(std::pair<string,string> (
                                              attribute.at(i),
                                              value.at(i)
                                             )
        );
    }
    convertToString();
   
}

void patientCSV::convertToString(){
     newData = "[{Patient ID:"+value.at(0)+"},";
     newData = newData+"{Last Name:"+value.at(1)+"},"; 	
     newData = newData+"{First Name:"+value.at(2)+"},"; 
     newData = newData+"{Middle Name:"+value.at(3)+"},";
     newData = newData+"{House Number:"+value.at(4)+"},";
     newData = newData+"{Street:"+value.at(5)+"},";
     newData = newData+"{City:"+value.at(6)+"},";
     newData = newData+"{Province:"+value.at(7)+"},";
     newData = newData+"{Birthday:"+value.at(8)+"},";
     newData = newData+"{Gender:"+value.at(9)+"},";
     newData = newData+"{Blood type:"+value.at(10)+"},";
     newData = newData+"{Weight:"+value.at(11)+"},";
     newData = newData+"{Height:"+value.at(12)+"},";
     newData = newData+"{Facility ID:"+value.at(13)+"},";
     newData = newData+"{Health Worker ID:"+value.at(14)+"}]\n";
}

void patientCSV::storeInJson()
{
    fstream file1;
    file1.open("PatientJson.json",ios::app);
    file1<<newData;
    file1.close();
}