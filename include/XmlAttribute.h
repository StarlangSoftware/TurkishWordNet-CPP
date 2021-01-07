//
// Created by Olcay Taner Yıldız on 12.10.2018.
//

#ifndef XMLPARSER_XMLATTRIBUTE_H
#define XMLPARSER_XMLATTRIBUTE_H
#include <string>

using namespace std;

class XmlAttribute {
private:
    string name;
    string value;
public:
    XmlAttribute();
    explicit XmlAttribute(string name);
    string getName();
    string getValue();
    void setValue(string value);
    string to_String();
};


#endif //XMLPARSER_XMLATTRIBUTE_H
