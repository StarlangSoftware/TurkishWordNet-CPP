//
// Created by olcay on 28.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_FSMPARSELIST_H
#define MORPHOLOGICALANALYSIS_FSMPARSELIST_H
#include "FsmParse.h"

class FsmParseList {
private:
    vector<FsmParse> fsmParses;
public:
    FsmParseList() = default;
    explicit FsmParseList(vector<FsmParse> fsmParses);
    int size();
    FsmParse getFsmParse(int index);
    string rootWords();
    void reduceToParsesWithSameRootAndPos(Word* currentWithPos);
    FsmParse getParseWithLongestRootWord();
    void reduceToParsesWithSameRoot(string currentRoot);
    vector<FsmParseList> constructParseListForDifferentRootWithPos();
    string parsesWithoutPrefixAndSuffix();
    string to_String();
};


#endif //MORPHOLOGICALANALYSIS_FSMPARSELIST_H
