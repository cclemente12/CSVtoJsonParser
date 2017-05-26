#include "patientCSV.h"
char pastChar;
int k= 0;
patientCSV::patientCSV() {
    //the start menu
    //Editted from here 1st edit
    int fileFlag = 1;
    fstream file;
    string empty;
    fstream ifile("patientEdit.json",ios::in);
    if (ifile) 
    {
        fileFlag = 0;
        int pos,i = 0;
       // ifile.open("patientEdit.json",ios::in);
        
        while(!ifile.eof())
       {
        getline(ifile,buffer);
        //cout<<"1";
        dup = strdup(buffer.c_str());
        pch = strtok (dup,"[{,}]");
            while (pch != NULL)
            {	
                 string s(pch);
                 pos=s.find(":");
               //  cout<<s.substr(pos+1,s.length()-1)<<endl;
                 value.push_back(s.substr(pos+1,s.length()-1));
                 pch = strtok (NULL, "[{,}]");
            }
        
        }
        convertToCSV();
        //remove("patientEdit.json");
        
    }
    
    //End of 1st edit
    if(fileFlag){
    file.open("requestJson.json",ios::in);
    while(!file.eof())
    {
        getline(file,buffer);
        dup = strdup(buffer.c_str());
        pch = strtok (dup,"[{,}]");
            while (pch != NULL)
            {	
                string s(pch);
                request.push_back(s);
                pch = strtok (NULL, "[{,}]");
            }
        [this]{
            for(auto i =0;i<3;i++)
                input[i].clear();};
        if(facilityDBSearch()&&healthWorker())
           // cout<<"tru";
            getAttribute();
    }
    file.close();
    }
    
}

patientCSV::patientCSV(const patientCSV& orig) {
    
}

patientCSV::~patientCSV() {
}
bool patientCSV::facilityDBSearch()
{
    int pos,i=0;
    for(int i = 0;i<request.size();i++){
        pos=request.at(i).find(":");
        if(request.at(i).substr(0,pos)=="Facility ID")
        {
           // cout<<request.at(i).substr(pos+1,request.at(i).length())<<endl;
           // return true;
            return searchInFacilityDB(request.at(i).substr(pos+1,request.at(i).length()));
            
        }
        
    }
    return false;
    
}
//CEDRICK EDIT
bool patientCSV::searchInFacilityDB(string search)
{
   // cout<<search<<endl;
    string buf;
    fstream file;
    file.open("FacilityDB.json",ios::in);
    while(!file.eof())
    {
        getline(file,buf);
        dup = strdup(buf.c_str());
        pch = strtok (dup,"[{,}]");
            while (pch != NULL)
            {	
                string s(pch);
                int pos1 = s.find(":");
              //  cout<<s.substr(pos1+1,s.length())<<endl;
                if(s.substr(pos1+1,s.length())==search){
                    return true;
                   // cout<<"asdasdasd";
                }
                    
                pch = strtok (NULL, "[{,}]");
            }
    }   
        return false;
}

//End Edit
bool patientCSV::healthWorker(){
    int pos,i=0;
    
    for(int i = 0;i<request.size();i++){
        pos=request.at(i).find(":");
        if(request.at(i).substr(0,pos)=="Health Worker ID")
        {
          
            return XML().healthWorkerFound(request.at(i).substr(pos+1,request.at(i).length()-1));
        
            
        }
        
    }
    return false;
    
}


void patientCSV::getAttribute()
{ ///
    
    int pos,i=0;
    for(int i = 0;i<request.size();i++){
        pos=request.at(i).find(":");
        if(request.at(i).substr(0,pos)=="Patient ID")
        {
            flagID=0;
      
            input[0] = request.at(i).substr(pos+1,request.at(i).length()-1);
            searchInFile();
            return;
        }
        
    }
    
    for(int i = 0;i<request.size();i++)
    {
        pos=request.at(i).find(":");
       if(request.at(i).substr(0,pos)=="Last Name")     
            input[0] = request.at(i).substr(pos+1,request.at(i).length()-1);
        else if(request.at(i).substr(0,pos)=="First Name")
            input[1] = request.at(i).substr(pos+1,request.at(i).length()-1);
        else if(request.at(i).substr(0,pos)=="Middle Name")
            input[2] = request.at(i).substr(pos+1,request.at(i).length()-1);
        
    }
    if(input[0]!=""&&input[1]!=""&&input[2]!=""){
        flagID=1;
        searchInFile();
    }
    
}

void patientCSV::searchInFile()
{
    //opening the csv file
    fstream file,file1;
    file.open("patient.csv", ios::in);
    //getting every line in file
    file1.open("PatientJson.json",ios::out|ios::trunc);
    file1.close();
    while(!file.eof())
    {
        string newText;
        getline(file,newText);
        //go searchCSVID function
        text = newText;
       // cout<<text<<endl;
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
    
//    for(int i=0;i<value.size();i++)
//    {
//        cout<<value.at(i)<<endl;
//    }
    //go pushToMap function
    //value.clear();
    //cout<<value.size()<<endl;
    pushToMap();   
}

void patientCSV::pushToMap(){ // MAP THE KEY-VALUE PAIR
    for(auto i = 0; i < attribute.size(); i++){
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
    file1.open("PatientJson.json",ios::app); 
    
    file1<<newData;
    value.clear();
    file1.close();
}
///Editted Here
void patientCSV::convertToCSV(){
    newData = newData+ value.at(0);
    cout<<value.size()<<endl;
    for(int i =1; i<value.size();i++)
    {
    newData = newData +","+value.at(i);    
    }
    editDataCSV();
}

void patientCSV::editDataCSV()
{
    fstream file1,file;
    string buf;
    file1.open("patient.csv",ios::in);
    file.open("temp.csv",ios::app);
    while(!file1.eof())
    {
       getline(file1,buf);
       int pos = buf.find(",");
       if(buf.substr(0,pos)==newData.substr(0,pos))
       {
           file<<newData<<endl;
       }
       else
       {
           file<<buf<<endl;
       }
    }
    file.close();
    file1.close();
    remove("patient.csv");
    rename("temp.csv","patient.csv");
}