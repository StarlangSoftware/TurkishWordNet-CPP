//
// Created by Olcay Taner Yıldız on 2.03.2019.
//

#ifndef MORPHOLOGICALANALYSIS_FSMMORPHOLOGICALANALYZER_H
#define MORPHOLOGICALANALYSIS_FSMMORPHOLOGICALANALYZER_H

#include <regex>
#include <set>
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
    set<string> parsedSurfaceForms;
    bool isPossibleSubstring(const string& shortString, const string& longString, TxtWord* root);
    void initializeParseList(vector<FsmParse>& fsmParse, TxtWord* root, bool isProper);
    void initializeParseListFromRoot(vector<FsmParse>& fsmParse, TxtWord* root, bool isProper);
    vector<FsmParse> initializeParseListFromSurfaceForm(const string& surfaceForm, bool isProper);
    void addNewParsesFromCurrentParse(FsmParse currentFsmParse, vector<FsmParse>& fsmParse, int maxLength, TxtWord* root);
    void addNewParsesFromCurrentParse(FsmParse currentFsmParse, vector<FsmParse>& fsmParse, const string& surfaceForm, TxtWord* root);
    bool parseExists(vector<FsmParse>& fsmParse, const string& surfaceForm);
    vector<FsmParse> parseWord(vector<FsmParse> fsmParse, int maxLength);
    vector<FsmParse> parseWord(vector<FsmParse> fsmParse, const string& surfaceForm);
    bool analysisExists(TxtWord* rootWord, const string& surfaceForm, bool isProper);
    vector<FsmParse> analysis(const string& surfaceForm, bool isProper);
    bool isInteger(const string& surfaceForm);
    bool isDouble(const string& surfaceForm);
    bool isNumber(string surfaceForm);
    bool isPercent(string surfaceForm);
    bool isTime(string surfaceForm);
    bool isRange(string surfaceForm);
    bool isDate(string surfaceForm);
    bool patternMatches(string expr, const string& value);
public:
    explicit FsmMorphologicalAnalyzer(string fileName = "turkish_finite_state_machine.xml", TxtDictionary dictionary = TxtDictionary(), int cacheSize = 10000);
    explicit FsmMorphologicalAnalyzer(string dictionaryFileName, string fileName = "turkish_finite_state_machine.xml");
    void addSurfaceForms(string fileName);
    TxtDictionary getDictionary();
    FiniteStateMachine getFiniteStateMachine();
    unordered_set<string> getPossibleWords(MorphologicalParse morphologicalParse, MetamorphicParse parse);
    vector<FsmParse> morphologicalAnalysis(TxtWord* root, const string& surfaceForm, string state);
    vector<FsmParse> generateAllParses(TxtWord* root, int maxLength);
    vector<FsmParse> morphologicalAnalysis(TxtWord* root, const string& surfaceForm);
    bool isProperNoun(const string& surfaceForm);
    FsmParseList robustMorphologicalAnalysis(const string& surfaceForm);
    FsmParseList* morphologicalAnalysis(Sentence& sentence);
    FsmParseList* robustMorphologicalAnalysis(Sentence& sentence);
    FsmParseList morphologicalAnalysis(const string& surfaceForm);
    bool morphologicalAnalysisExists(TxtWord* rootWord, string surfaceForm);
};


#endif //MORPHOLOGICALANALYSIS_FSMMORPHOLOGICALANALYZER_H
