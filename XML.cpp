#include "XML.h"

const char openToken = '<';
const char closeToken = '/';
int XML::ct;
XML::XML() { ct++;}

XML::XML(string xml){
    ct++;cout << "\nXML created "<<ct;
    string text;
    text = getAttributes(xml);
    populateKeyValuePair(text);
}

XML::XML(const XML& orig) {}

XML::~XML() {ct--;}

//void XML::SetChild(XML child) { this->child = child; }
//XML XML::GetChild() const { return child; }

string XML::getAttributes(string xml)
{
    string text,object;
    bool open=false;
    for(string::iterator i=xml.begin() ; i != xml.end() ; i++)
    {
        if((*i) == openToken ) {  open = true;  continue;}
        else if((*i) == ' ' ) { open=false;  continue;}
        if(open) { text += (*i); }
        else
        {
            object = text;
            text.clear();
            text = xml.substr( //indented for readability
                                xml.find_first_of(object)+object.length()+1 ,
                                xml.length()-(xml.find_first_of(object)+object.length()+1)- (xml.length()-(xml.find_last_of("/")))
                            );
            break;
        }
    }
    return text;
}

void XML::populateKeyValuePair(string text)
{
    bool isKey=true,isPair=false;
    string key,value;
    for(string::iterator i=text.begin() ; i != text.end() ; i++)
    {
        if(isPair)
        {
            SetPair(key,value);
            key.clear(); value.clear();
            isPair=false;
        }
        if(isKey)
        {
            if((*i)=='=') { isKey=false; continue; }
            key += (*i);
        }
        else if(!isKey)
        {
            if((*i)==' ') { isKey=true; isPair = true; continue; }
            value += (*i);
        }
    }
}

void XML::SetPair(string key,string value) { pair.insert(std::pair<string,string>(key,value)); }

void XML::SetPair(map<string, string>::iterator b,map<string, string>::iterator e) { pair.insert(b,e); }

map<string, string> XML::GetPair() const { return pair; }

void XML::display()
{
    for(map<string,string>::iterator i=pair.begin() ; i !=pair.end() ; i++ )
    {
        cout <<endl << "Key: "<< (*i).first << " Value: " << (*i).second;
    }
}

void XML::SetXMLName(string XMLName) { this->XMLName = XMLName; }

string XML::GetXMLName() const { return XMLName; }

void XML::createXmlFile()
{
    ofstream fout("patient_TEMP.xml",ios::app);
    string xml;
    string open = "<"+GetXMLName();
    string end = " />";

    for(map<string,string>::iterator i=pair.begin() ; i !=pair.end() ; i++ )
        xml += " " + (*i).first + "=" +(*i).second;

    fout << open + xml + end + "\n";
    fout.close();
}

string XML::GetAttributeValue(string attribute)
{
    return pair[attribute].data();
}
bool XML::healthWorkerFound(string hID)                                                     
{
    ifstream hwDB("healthworker.xml");
    string hwrecord;
    while(!hwDB.eof())
    {
        getline(hwDB,hwrecord);
        if(hwrecord.length() > 0)
        {
            populateKeyValuePair(getAttributes(hwrecord));
            if(pair["Health Worker ID"] == hID) return true;
            else pair.clear();
        }
    }
    hwDB.close();
    return false;
}
