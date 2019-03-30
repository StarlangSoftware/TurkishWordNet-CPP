//
// Created by Olcay Taner YILDIZ on 2019-03-23.
//

#ifndef WORDNET_SYNSET_H
#define WORDNET_SYNSET_H

#include <string>
#include <vector>
#include "Pos.h"
#include "Synonym.h"

using namespace std;

class SynSet {
private:
    string id;
    Pos pos;
    vector<string> definition;
    string example;
    Synonym synonym;
    vector<Relation*> relations;
    string note;
    int bcs;
public:
    bool operator==(const SynSet &anotherSynSet) const{
        return (id == anotherSynSet.id);
    }
    SynSet() = default;
    explicit SynSet(string id);
    string getId();
    void setId(string id);
    void setDefinition(string definition);
    void removeDefinition(string definition);
    void removeSameDefinitions();
    string getDefinition();
    string representative();
    string getLongDefinition();
    void sortDefinitions();
    string getDefinition(int index);
    int numberOfDefinitions();
    void setExample(string example);
    string getExample();
    void setBcs(int bcs);
    int getBcs();
    void setPos(Pos pos);
    Pos getPos();
    void setNote(string note);
    string getNote();
    void addRelation(Relation* relation);
    void removeRelation(Relation* relation);
    void removeRelation(string name);
    Relation* getRelation(int index);
    vector<string> getInterlingual();
    int relationSize();
    void addLiteral(Literal literal);
    Synonym getSynonym();
    bool containsSameLiteral(SynSet synSet);
    bool containsRelation(Relation* relation);
    bool containsRelationType(SemanticRelationType semanticRelationType);
    void mergeSynSet(SynSet synSet);
    string to_string();
    void saveAsXml(ofstream& outfile);
};


#endif //WORDNET_SYNSET_H
