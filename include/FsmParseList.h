//
// Created by olcay on 28.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_FSMPARSELIST_H
#define MORPHOLOGICALANALYSIS_FSMPARSELIST_H
#include "FsmParse.h"

class FsmParseList {
private:
    vector<FsmParse> fsmParses;
    string defaultCaseForParseString(string rootForm, string parseString, string partOfSpeech);
public:
    FsmParseList() = default;
    explicit FsmParseList(vector<FsmParse> fsmParses);
    int size();
    FsmParse getFsmParse(int index);
    string rootWords();
    void reduceToParsesWithSameRootAndPos(Word* currentWithPos);
    void reduceToParsesWithSameRoot(string currentRoot);
    FsmParse caseDisambiguator();
    vector<FsmParseList> constructParseListForDifferentRootWithPos();
    string parsesWithoutPrefixAndSuffix();
    string to_String();
};


#endif //MORPHOLOGICALANALYSIS_FSMPARSELIST_H
