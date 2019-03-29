//
// Created by Olcay Taner Yıldız on 12.10.2018.
//

#ifndef XMLPARSER_XMLDOCUMENT_H
#define XMLPARSER_XMLDOCUMENT_H
#include <string>
#include <fstream>
#include "XmlElement.h"
#include "XmlTokenType.h"

using namespace std;

class XmlDocument {
private:
    string fileName;
    ifstream inputStream;
    XmlTokenType lastReadTokenType = XmlTokenType::XML_END;
    XmlElement* root;
    string readToken(char previousChar, char* nextChar, bool extraAllowed);
    string parseTag();
    string parseAttributeValue();
    string parseEmptyTag();
    string getNextToken();
public:
    explicit XmlDocument(string fileName);
    ~XmlDocument();
    void print(string fileName);
    void parse();
    XmlElement* getFirstChild();
};


#endif //XMLPARSER_XMLDOCUMENT_H
