#include "patientCSV.h"
char pastChar;

patientCSV::patientCSV() {
    //the start menu
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
            flagID=0;
            //Go searchInFile function
            searchInFile(input);
            
    }
//    Enter Option 2
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
            
    }
    
}

patientCSV::patientCSV(const patientCSV& orig) {
}

patientCSV::~patientCSV() {
}

void patientCSV::searchInFile(string* input)
{
    //opening the csv file
    fstream file;
    file.open("patient.csv", ios::in);
    //getting every line in file
    while(!file.eof())
    {
        string newText;
        getline(file,newText);
        //go searchCSVID function
        text = newText;
        searchCSVID(text);
    }
    file.close();
}


void patientCSV::searchCSVID(string text)
{
  string temporary;
  int ctr=0;
    //to get every attribute value in file seperated with comma
    for(auto i=text.begin() ; i != text.end(); ++i) 
    {   
        //attribute value is empty
        if((*i) == ',' && pastChar == ',')
        {
            temporary += "";
        }
        //getting the alphanumeric value in file
        if((*i) != ',')
        {
            temporary += (*i);
        }
        //condition for checking if value i is a comma
        if ((*i) == ',')
        {
            
            ctr++;
            //if searching by ID, condition if inputted ID is not equal to temporary
            if(input[0]!=temporary&&ctr==1&&flagID==0)
                //return if true;
                return;
            //if searching by Name, condition if inputted Name is not equal to temporary until Middle name
            else if(((input[0]!=temporary&&ctr==2) || (input[1]!=temporary&&ctr==3) || (input[2]!=temporary&&ctr==4))&&flagID==1){
                //clear the stored vector value then return
                value.clear();
                return;
            }
         //if value i is comma, store temporary in vector value.
            value.push_back(temporary);
            //clear temporary
            temporary.clear();
        }
        //store past character
        pastChar = (*i);
    }
    //storing the last value in csv file
    value.push_back(temporary);
    //go pushToMap function
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
    //go convertToString function
    convertToString();
   
}

void patientCSV::convertToString(){
     //creating a json format string through vector value data
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
     storeInJson();
}

void patientCSV::storeInJson()//appending in Json file
{
    fstream file1;
    if(flagFirstData)
    {
    file1.open("PatientJson.json",ios::in);
    flagFirstData=false;
    }
    else{
    file1.open("PatientJson.json",ios::app); 
    }
    file1<<newData;
    value.clear();
    file1.close();
}