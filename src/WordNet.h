//
// Created by olcay on 29.03.2019.
//

#ifndef WORDNET_WORDNET_H
#define WORDNET_WORDNET_H

#include <map>
#include <unordered_map>
#include <MorphologicalParse.h>
#include <MetamorphicParse.h>
#include <FsmMorphologicalAnalyzer.h>
#include "Dictionary/ExceptionalWord.h"
#include "SynSet.h"
#include "SemanticRelation.h"

using namespace std;

class WordNet {
private:
    map<string, SynSet> synSetList;
    map<string, vector<Literal>> literalList;
    unordered_map<string, ExceptionalWord> exceptionList;
    unordered_map<string, vector<SynSet>> interlingualList;
    void addSynSetsWithLiteralToList(vector<SynSet>& result, const string& literal, Pos pos);
    void multipleInterlingualRelationCheck1(WordNet secondWordNet);
    void multipleInterlingualRelationCheck2(WordNet secondWordNet);
    void sameLiteralSameSenseCheck() const;
    void sameLiteralSameSynSetCheck() const;
    void noDefinitionCheck() const;
    void semanticRelationNoIDCheck();
    void sameSemanticRelationCheck() const;
    pair<string, int> findLCS(const vector<string>& pathToRootOfSynSet1, const vector<string>& pathToRootOfSynSet2) const;
public:
    void readWordNet(const string& fileName);
    void readExceptionFile(const string& exceptionFileName);
    WordNet();
    explicit WordNet(const string& fileName);
    WordNet(const string& fileName, const string& exceptionFileName);
    void addLiteralToLiteralList(const Literal& literal);
    void mergeSynSets(const string& synSetFile);
    vector<SynSet> getSynSetList() const;
    vector<string> getLiteralList() const;
    map<string, SynSet>::iterator addSynSet(const SynSet& synSet);
    void removeSynSet(const SynSet& s);
    void changeSynSetId(SynSet s, const string& newId);
    SynSet* getSynSetWithId(const string& synSetId);
    SynSet* getSynSetWithLiteral(const string& literal, int sense);
    int numberOfSynSetsWithLiteral(const string& literal) const;
    vector<SynSet> getSynSetsWithPartOfSpeech(Pos pos) const;
    vector<Literal> getLiteralsWithName(const string& literal) const;
    vector<SynSet> getSynSetsWithLiteral(const string& literal);
    vector<string> getLiteralsWithPossibleModifiedLiteral(const string& literal) const;
    vector<SynSet> getSynSetsWithPossiblyModifiedLiteral(const string& literal, Pos pos);
    void addReverseRelation(const SynSet& synSet, const SemanticRelation& semanticRelation);
    void removeReverseRelation(const SynSet& synSet, const SemanticRelation& semanticRelation);
    void equalizeSemanticRelations();
    vector<Literal> constructLiterals(const string& word, const MorphologicalParse& parse, const MetamorphicParse& metaParse, FsmMorphologicalAnalyzer fsm) const;
    vector<SynSet> constructSynSets(const string& word, const MorphologicalParse& parse, const MetamorphicParse& metaParse, FsmMorphologicalAnalyzer fsm);
    vector<Literal> constructIdiomLiterals(const MorphologicalParse& morphologicalParse1, const MorphologicalParse& morphologicalParse2, const MorphologicalParse& morphologicalParse3, const MetamorphicParse& metaParse1, const MetamorphicParse& metaParse2, const MetamorphicParse& metaParse3, FsmMorphologicalAnalyzer fsm) const;
    vector<SynSet> constructIdiomSynSets(const MorphologicalParse& morphologicalParse1, const MorphologicalParse& morphologicalParse2, const MorphologicalParse& morphologicalParse3, const MetamorphicParse& metaParse1, const MetamorphicParse& metaParse2, const MetamorphicParse& metaParse3, FsmMorphologicalAnalyzer fsm);
    vector<Literal> constructIdiomLiterals(const MorphologicalParse& morphologicalParse1, const MorphologicalParse& morphologicalParse2, const MetamorphicParse& metaParse1, const MetamorphicParse& metaParse2, FsmMorphologicalAnalyzer fsm) const;
    vector<SynSet> constructIdiomSynSets(const MorphologicalParse& morphologicalParse1, const MorphologicalParse& morphologicalParse2, const MetamorphicParse& metaParse1, const MetamorphicParse& metaParse2, FsmMorphologicalAnalyzer fsm);
    void sortDefinitions();
    vector<SynSet> getInterlingual(const string& synSetId) const;
    void check(const WordNet& secondWordNet);
    void saveAsXml(const string& fileName) const;
    int size() const;
    int findPathLength(const vector<string>& pathToRootOfSynSet1, const vector<string>& pathToRootOfSynSet2) const;
    int findLCSdepth(const vector<string>& pathToRootOfSynSet1, const vector<string>& pathToRootOfSynSet2) const;
    string findLCSid(const vector<string>& pathToRootOfSynSet1, const vector<string>& pathToRootOfSynSet2) const;
    vector<string> findPathToRoot(SynSet* synset);
    SynSet* percolateUp(SynSet* root);
};


#endif //WORDNET_WORDNET_H
