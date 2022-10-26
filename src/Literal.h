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
    Literal(const string& name, int sense, const string& synSetId);
    string getSynSetId() const;
    string getName() const;
    int getSense() const;
    string getOrigin() const;
    void setOrigin(const string& origin);
    void setSense(int sense);
    void addRelation(Relation* relation);
    void removeRelation(Relation* relation);
    bool containsRelation(Relation* relation) const;
    bool containsRelationType(SemanticRelationType semanticRelationType) const;
    Relation* getRelation(int index) const;
    int relationSize() const;
    void setName(const string& name);
    void setSynSetId(const string& synSetId);
    string to_string() const;
    void saveAsXml(ofstream& outfile);
};


#endif //WORDNET_LITERAL_H
