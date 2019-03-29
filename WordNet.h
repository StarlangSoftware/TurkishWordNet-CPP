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
#include "ExceptionalWord.h"
#include "SynSet.h"
#include "SemanticRelation.h"

using namespace std;

class WordNet {
private:
    map<string, SynSet> synSetList;
    map<string, vector<Literal>> literalList;
    unordered_map<string, ExceptionalWord> exceptionList;
    unordered_map<string, vector<SynSet>> interlingualList;
    void addSynSetsWithLiteralToList(vector<SynSet> result, string literal, Pos pos);
public:
    void readWordNet(string fileName);
    void readExceptionFile(string exceptionFileName);
    WordNet();
    explicit WordNet(string fileName);
    WordNet(string fileName, string exceptionFileName);
    void addLiteralToLiteralList(Literal literal);
    void mergeSynSets(string synSetFile);
    vector<SynSet> getSynSetList();
    vector<string> getLiteralList();
    void addSynSet(SynSet synSet);
    void removeSynSet(SynSet s);
    SynSet getSynSetWithId(string synSetId);
    SynSet getSynSetWithLiteral(string literal, int sense);
    int numberOfSynSetsWithLiteral(string literal);
    vector<SynSet> getSynSetsWithPartOfSpeech(Pos pos);
    vector<Literal> getLiteralsWithName(string literal);
    vector<SynSet> getSynSetsWithLiteral(string literal);
    vector<string> getLiteralsWithPossibleModifiedLiteral(string literal);
    vector<SynSet> getSynSetsWithPossiblyModifiedLiteral(string literal, Pos pos);
    void addReverseRelation(SynSet synSet, SemanticRelation semanticRelation);
    void removeReverseRelation(SynSet synSet, SemanticRelation semanticRelation);
    void equalizeSemanticRelations();
    vector<Literal> constructLiterals(string word, MorphologicalParse parse, MetamorphicParse metaParse, FsmMorphologicalAnalyzer fsm);
    vector<SynSet> constructSynSets(string word, MorphologicalParse parse, MetamorphicParse metaParse, FsmMorphologicalAnalyzer fsm);
    vector<Literal> constructIdiomLiterals(MorphologicalParse morphologicalParse1, MorphologicalParse morphologicalParse2, MorphologicalParse morphologicalParse3, MetamorphicParse metaParse1, MetamorphicParse metaParse2, MetamorphicParse metaParse3, FsmMorphologicalAnalyzer fsm);
    vector<SynSet> constructIdiomSynSets(MorphologicalParse morphologicalParse1, MorphologicalParse morphologicalParse2, MorphologicalParse morphologicalParse3, MetamorphicParse metaParse1, MetamorphicParse metaParse2, MetamorphicParse metaParse3, FsmMorphologicalAnalyzer fsm);
    vector<Literal> constructIdiomLiterals(MorphologicalParse morphologicalParse1, MorphologicalParse morphologicalParse2, MetamorphicParse metaParse1, MetamorphicParse metaParse2, FsmMorphologicalAnalyzer fsm);
    vector<SynSet> constructIdiomSynSets(MorphologicalParse morphologicalParse1, MorphologicalParse morphologicalParse2, MetamorphicParse metaParse1, MetamorphicParse metaParse2, FsmMorphologicalAnalyzer fsm);
    void sortDefinitions();
    vector<SynSet> getInterlingual(string synSetId);
};


#endif //WORDNET_WORDNET_H
