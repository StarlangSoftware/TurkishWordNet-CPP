//
// Created by Olcay Taner YILDIZ on 2019-03-23.
//

#ifndef WORDNET_SYNSET_H
#define WORDNET_SYNSET_H

#include <string>
#include <vector>
#include "Dictionary/Pos.h"
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
    string wikiPage;
    int bcs;
public:
    bool operator==(const SynSet &anotherSynSet) const{
        return (id == anotherSynSet.id);
    }
    SynSet() = default;
    explicit SynSet(const string& id);
    string getId() const;
    void setId(const string& _id);
    void setDefinition(const string& _definition);
    void removeDefinition(const string& _definition);
    void removeSameDefinitions();
    string getDefinition() const;
    string representative() const;
    string getLongDefinition() const;
    void sortDefinitions();
    string getDefinition(int index) const;
    int numberOfDefinitions() const;
    void setExample(const string& _example);
    string getExample() const;
    void setBcs(int _bcs);
    int getBcs() const;
    void setPos(Pos _pos);
    Pos getPos() const;
    void setNote(const string& _note);
    string getNote() const;
    void setWikiPage(const string& _wikiPage);
    string getWikiPage() const;
    void addRelation(Relation* relation);
    void removeRelation(Relation* relation);
    void removeRelation(const string& name);
    Relation* getRelation(int index) const;
    vector<string> getInterlingual() const;
    int relationSize() const;
    void addLiteral(const Literal& literal);
    Synonym getSynonym() const;
    bool containsSameLiteral(const SynSet& synSet) const;
    bool containsRelation(Relation* relation) const;
    bool containsRelationType(SemanticRelationType semanticRelationType) const;
    void mergeSynSet(const SynSet& synSet);
    string to_string() const;
    void saveAsXml(ofstream& outfile);
};


#endif //WORDNET_SYNSET_H
