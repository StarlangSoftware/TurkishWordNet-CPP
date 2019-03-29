//
// Created by Olcay Taner Yıldız on 2.03.2019.
//

#ifndef MORPHOLOGICALANALYSIS_FSMMORPHOLOGICALANALYZER_H
#define MORPHOLOGICALANALYSIS_FSMMORPHOLOGICALANALYZER_H

#include <regex>
#include "Trie.h"
#include "Sentence.h"
#include "FiniteStateMachine.h"
#include "TxtDictionary.h"
#include "LRUCache.h"
#include "FsmParseList.h"
#include "MetamorphicParse.h"

class FsmMorphologicalAnalyzer {
private:
    Trie* dictionaryTrie;
    FiniteStateMachine finiteStateMachine;
    int MAX_DISTANCE = 2;
    TxtDictionary dictionary;
    LRUCache<string, FsmParseList> cache;
    map<string, regex> mostUsedPatterns;
    bool isPossibleSubstring(string shortString, string longString, TxtWord* root);
    void initializeParseList(vector<FsmParse>& fsmParse, TxtWord* root, bool isProper);
    vector<FsmParse> initializeRootList(string surfaceForm, bool isProper);
    void addNewParsesFromCurrentParse(FsmParse currentFsmParse, vector<FsmParse>& fsmParse, string surfaceForm, TxtWord* root);
    bool parseExists(vector<FsmParse>& fsmParse, string surfaceForm);
    vector<FsmParse> parseWord(vector<FsmParse> fsmParse, string surfaceForm);
    bool analysisExists(TxtWord* rootWord, string surfaceForm, bool isProper);
    vector<FsmParse> analysis(string surfaceForm, bool isProper);
    bool isInteger(string surfaceForm);
    bool isDouble(string surfaceForm);
    bool isNumber(string surfaceForm);
    bool patternMatches(string expr, string value);
public:
    explicit FsmMorphologicalAnalyzer(string fileName = "turkish_finite_state_machine.xml", TxtDictionary dictionary = TxtDictionary(), int cacheSize = 10000);
    explicit FsmMorphologicalAnalyzer(string dictionaryFileName, string fileName = "turkish_finite_state_machine.xml");
    TxtDictionary getDictionary();
    FiniteStateMachine getFiniteStateMachine();
    unordered_set<string> getPossibleWords(MorphologicalParse morphologicalParse, MetamorphicParse parse);
    vector<FsmParse> morphologicalAnalysis(TxtWord* root, string surfaceForm, string state);
    vector<FsmParse> morphologicalAnalysis(TxtWord* root, string surfaceForm);
    bool isProperNoun(string surfaceForm);
    FsmParseList robustMorphologicalAnalysis(string surfaceForm);
    FsmParseList* morphologicalAnalysis(Sentence sentence, bool debugMode);
    FsmParseList* robustMorphologicalAnalysis(Sentence sentence);
    FsmParseList morphologicalAnalysis(string surfaceForm);
    bool morphologicalAnalysisExists(TxtWord* rootWord, string surfaceForm);
};


#endif //MORPHOLOGICALANALYSIS_FSMMORPHOLOGICALANALYZER_H
