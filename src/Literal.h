//
// Created by olcay on 21.03.2019.
//

#ifndef WORDNET_LITERAL_H
#define WORDNET_LITERAL_H

#include <string>
#include <vector>
#include "Relation.h"
#include "SemanticRelationType.h"

using namespace std;

class Literal {
protected:
    string name;
    int sense;
    string synSetId;
    string origin;
    vector<Relation*> relations;
public:
    bool operator==(const Literal &anotherLiteral) const{
        return (name == anotherLiteral.name && sense == anotherLiteral.sense);
    }
    Literal() = default;
    Literal(string name, int sense, string synSetId);
    string getSynSetId();
    string getName();
    int getSense();
    string getOrigin();
    void setOrigin(string origin);
    void setSense(int sense);
    void addRelation(Relation* relation);
    void removeRelation(Relation* relation);
    bool containsRelation(Relation* relation);
    bool containsRelationType(SemanticRelationType semanticRelationType);
    Relation* getRelation(int index);
    int relationSize();
    void setName(string name);
    void setSynSetId(string synSetId);
    string to_string();
    void saveAsXml(ofstream& outfile);
};


#endif //WORDNET_LITERAL_H
