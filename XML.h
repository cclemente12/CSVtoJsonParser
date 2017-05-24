#ifndef XML_H
#define XML_H

#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

class XML
{
    public:
      XML();
      XML(string s);
      XML(const XML& orig);
      virtual ~XML();
      void SetPair(string key,string value);
      void SetPair(map<string, string>::iterator b,map<string, string>::iterator e);
      map<string, string> GetPair() const;
      void populateKeyValuePair(string text);
      string getAttributes(string xml);
      void createXmlFile();
      void display();
      void SetXMLName(string XMLName);
      string GetXMLName() const;
      
      string GetAttributeValue(string attribute);                     
      bool healthWorkerFound(string hID);                                  
    protected:

    private:
      string XMLName;
      map<string,string> pair;
      static int ct;
};

#endif // XML_H