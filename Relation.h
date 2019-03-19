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
    explicit Relation(string name);
    string getName();
    void setName(string name);
    bool operator==(const Relation &anotherRelation) const{
        return (name == anotherRelation.name);
    }
};


#endif //WORDNET_RELATION_H
