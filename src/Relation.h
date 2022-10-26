//
// Created by olcay on 19.03.2019.
//

#ifndef WORDNET_RELATION_H
#define WORDNET_RELATION_H

#include <string>

using namespace std;

class Relation {
protected:
    string name;
public:
    explicit Relation(const string& name);
    string getName() const;
    void setName(const string& name);
    virtual string getTypeAsString() const = 0;
    virtual string to_xml() const = 0;
    bool operator==(const Relation &anotherRelation) const{
        return (name == anotherRelation.name);
    }
};


#endif //WORDNET_RELATION_H
