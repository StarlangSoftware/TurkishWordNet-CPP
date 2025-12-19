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
    int sense = 0;
    string synSetId;
    string origin;
    int groupNo = 0;
    vector<Relation*> relations;
public:
    bool operator==(const Literal &anotherLiteral) const{
        return (name == anotherLiteral.name && sense == anotherLiteral.sense);
    }
    Literal() = default;
    Literal(const string& name, int sense, const string& synSetId);
    [[nodiscard]] string getSynSetId() const;
    [[nodiscard]] string getName() const;
    [[nodiscard]] int getSense() const;
    [[nodiscard]] string getOrigin() const;
    [[nodiscard]] int getGroupNo() const;
    void setGroupNo(int groupNo);
    void setOrigin(const string& origin);
    void setSense(int sense);
    void addRelation(Relation* relation);
    void removeRelation(const Relation* relation);
    bool containsRelation(const Relation* relation) const;
    [[nodiscard]] bool containsRelationType(SemanticRelationType semanticRelationType) const;
    [[nodiscard]] Relation* getRelation(int index) const;
    [[nodiscard]] int relationSize() const;
    void setName(const string& name);
    void setSynSetId(const string& synSetId);
    [[nodiscard]] string to_string() const;
    void saveAsXml(ofstream& outfile) const;
};


#endif //WORDNET_LITERAL_H
