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
    [[nodiscard]] string getId() const;
    void setId(const string& _id);
    void setDefinition(const string& _definition);
    void removeDefinition(const string& _definition);
    void removeSameDefinitions();
    [[nodiscard]] string getDefinition() const;
    [[nodiscard]] string representative() const;
    [[nodiscard]] string getLongDefinition() const;
    void sortDefinitions();
    [[nodiscard]] string getDefinition(int index) const;
    [[nodiscard]] int numberOfDefinitions() const;
    void setExample(const string& _example);
    [[nodiscard]] string getExample() const;
    void setBcs(int _bcs);
    [[nodiscard]] int getBcs() const;
    void setPos(Pos _pos);
    [[nodiscard]] Pos getPos() const;
    void setNote(const string& _note);
    [[nodiscard]] string getNote() const;
    void setWikiPage(const string& _wikiPage);
    [[nodiscard]] string getWikiPage() const;
    void addRelation(Relation* relation);
    void removeRelation(const Relation* relation);
    void removeRelation(const string& name);
    [[nodiscard]] Relation* getRelation(int index) const;
    [[nodiscard]] vector<string> getInterlingual() const;
    [[nodiscard]] int relationSize() const;
    void addLiteral(const Literal& literal);
    [[nodiscard]] Synonym getSynonym() const;
    [[nodiscard]] bool containsSameLiteral(const SynSet& synSet) const;
    bool containsRelation(const Relation* relation) const;
    [[nodiscard]] bool containsRelationType(SemanticRelationType semanticRelationType) const;
    void mergeSynSet(const SynSet& synSet);
    [[nodiscard]] string to_string() const;
    void saveAsXml(ofstream& outfile) const;
};


#endif //WORDNET_SYNSET_H
